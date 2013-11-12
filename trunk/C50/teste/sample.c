/*************************************************************************/
/*									 */
/*	 Source code for use with See5/C5.0 Release 2.10		 */
/*	 -----------------------------------------------		 */
/*		       Copyright RuleQuest Research 2013		 */
/*									 */
/*	This code is provided "as is" without warranty of any kind,	 */
/*	either express or implied.  All use is at your own risk.	 */
/*									 */
/*************************************************************************/


/*************************************************************************/
/*									 */
/*	Sample program to demonstrate the use of See5/C5.0 classifiers	 */
/*	--------------------------------------------------------------	 */
/*									 */
/*	Compilation:							 */
/*									 */
/*	    Unix: use an ANSI C compiler such as gcc and include	 */
/*		  the math library, e.g. gcc sample.c -lm		 */
/*									 */
/*	    Windows: compile as a console application with symbol	 */
/*		  "WIN32" defined					 */
/*									 */
/*	This program accepts three command-line options:		 */
/*									 */
/*	    -f <filestem>   specify the application name (required)	 */
/*	    -r		    use rulesets instead of decision trees	 */
/*	    -R		    use rulesets and show rules used		 */
/*	    -x		    use a similar format as saved by the	 */
/*			    See5 cross-reference window			 */
/*									 */
/*	The program expects to find the following files:		 */
/*									 */
/*	    <filestem>.names (the application names file)		 */
/*									 */
/*	    <filestem>.rules or <filestem>.tree (the classifier	files	 */
/*		 generated by C5.0 or See5)			 	 */
/*									 */
/*	    <filestem>.costs (optional -- the  costs file)		 */
/*									 */
/*	    <filestem>.cases (with a format similar to a .data file, but */
/*		allowing classes to be given as '?' meaning 'unknown')	 */
/*									 */
/*	Please note: the names file must be exactly as it was when	 */
/*	the classifier was generated.					 */
/*									 */
/*	For each case in <filestem.cases>, the program prints the	 */
/*	given class and then the class predicted by the classifier	 */
/*	together with the confidence of the prediction.			 */
/*									 */
/*	Revised March 2013						 */
/*									 */
/*************************************************************************/

//#include "defns.h"
/*************************************************************************/
/*									 */
/*	Source code for use with See5/C5.0 Release 2.10			 */
/*	-----------------------------------------------			 */
/*		      Copyright RuleQuest Research 2013			 */
/*									 */
/*	This code is provided "as is" without warranty of any kind,	 */
/*	either express or implied.  All use is at your own risk.	 */
/*									 */
/*************************************************************************/

#include "../treino/defns.i"
#include "../treino/extern.i"

typedef	 struct _classify_environment
	 {
	    CaseNo	Fp;		/* for SMP */
	    double	*ClassWt;	/* total class votes */
	    float	*Vote,		/* class boost votes */
			Confidence;	/* prediction CF */
	    RuleNo	*Active,	/* active rules */
			ActiveSpace,	/* space for same */
			NActive;	/* number of same */
	    CRule	*MostSpec;	/* most specific active rules */
	    Boolean	*AttUsed;	/* reserved for possible later use */
	    RuleNo	*RulesUsed,	/* all applicable rules */
			NRulesUsed;	/* number of same */
	 }
	 CEnvRec, *CEnv;

CEnvRec		*GCEnv;		/* used by classification routines */


void FreeGlobals()
/*   -----------  */
{
    /*  Free memory allocated for classifier  */

    if ( RULES )
    {
	ForEach(Trial, 0, TRIALS-1)
	{
	     FreeRules(RuleSet[Trial]);
	}
	free(RuleSet);

	FreeUnlessNil(GCEnv->Active);
	FreeUnlessNil(GCEnv->RulesUsed);
	FreeUnlessNil(GCEnv->MostSpec);
    }
    else
    {
	ForEach(Trial, 0, TRIALS-1)
	{
	     FreeTree(Pruned[Trial]);
	}
	free(Pruned);
    }

//    FreeUnlessNil(PropVal);

    /*  Free memory allocated for cost matrix  */

    if ( MCost )
    {
        FreeVector((void **) MCost, 1, MaxClass);
    }

    /*  Free memory for names etc  */

    FreeNames();
    FreeUnlessNil(IgnoredVals);

    free(GCEnv->ClassWt);
    free(GCEnv->Vote);
    free(GCEnv);
}


int c50classif(char *baseFileName)
/*  ----  */
{
    FILE		*F, *out;
    DataRec		Case;
    int			MaxClassLen=5, o, TotalRules=0,
			StartList, CurrentPosition;
    ClassNo		Predict, c;
    Boolean		XRefForm=false, RULESUSED=false;

    char outputFileName[256];
    void		ShowRules(int);

    /*  Read information on attribute names, values, and classes  */
    FileStem = baseFileName;
    if ( ! (F = GetFile(".names", "r")) ) Error(NOFILE, Fn, "");

    GetNames(F);

    strcpy(outputFileName, baseFileName);
    strcat(outputFileName, ".out");
    out = fopen(outputFileName, "w");

    /*  Set up the classification environment  */

    GCEnv = AllocZero(1, CEnvRec);

    GCEnv->ClassWt    = Alloc(MaxClass+1, double);
    GCEnv->Vote       = Alloc(MaxClass+1, float);

    /*  Read the appropriate classifier file.  Call CheckFile() to
	determine the number of trials, then allocate space for
	trees or rulesets  */

    if ( RULES )
    {
	CheckFile(".rules", false);
	RuleSet = AllocZero(TRIALS+1, CRuleSet);

	ForEach(Trial, 0, TRIALS-1)
	{
	    RuleSet[Trial] = GetRules(".rules");
	    TotalRules += RuleSet[Trial]->SNRules;
	}

	if ( RULESUSED )
	{
	    GCEnv->RulesUsed = Alloc(TotalRules + TRIALS, RuleNo);
	}

	GCEnv->MostSpec   = Alloc(MaxClass+1, CRule);
    }
    else
    {
	CheckFile(".tree", false);
	Pruned = AllocZero(TRIALS+1, Tree);

	ForEach(Trial, 0, TRIALS-1)
	{
	    Pruned[Trial] = GetTree(".tree");
	}
    }

    /*  Close the classifier file and reset the file variable  */

    fclose(TRf);
    TRf = 0;

    /*  Set global default class for boosting  */

    Default = ( RULES ? RuleSet[0]->SDefault : Pruned[0]->Leaf );

    /*  Now classify the cases in file <filestem>.cases.
	This has the same format as a .data file except that
	the class can be "?" to indicate that it is unknown.  */

    if ( XRefForm )
    {
	ForEach(c, 1, MaxClass)
	{
	    if ( (o = strlen(ClassName[c])) > MaxClassLen ) MaxClassLen = o;
	}

//	printf("%-15s %*s   [Predicted]%s\n\n",
//	       "Case", -MaxClassLen, "Class",
//	       ( RULESUSED ? "   Rules" : "" ));

	StartList = 16 + MaxClassLen + 3 +
		    ( MaxClassLen > 9 ? MaxClassLen + 2 : 11 ) + 3;
    }
    else
    {
//	printf("Case\t\tGiven\t\tPredicted%s\n %s\t\tClass\t\tClass\n\n",
//		( RULESUSED ? "\t\t    Rules" : "" ),
//		( LabelAtt ? "ID" : "No" ));

	StartList = 60;
    }

    if ( ! (F = GetFile(".cases", "r")) ) Error(NOFILE, Fn, "");

    LineNo = 0;

    while ( (Case = GetDataRec(F, false)) )
    {
	/*  For this case, find the class predicted by See5/C5.0 model  */

	Predict = Classify(Case);//, GCEnv);

	/*  Print either case label or number  */

	if ( LabelAtt )
	{
//	    printf("%-15.15s ", (String) (IgnoredVals + SVal(Case,LabelAtt)));
	}
	else
	{
//	    printf("%4d\t\t", ++CaseNo);
	}

	/*  Print the result for this case in alternative formats  */

	if ( XRefForm )
	{
//	    printf("%*s", -MaxClassLen, ClassName[Class(Case)]);
	    CurrentPosition = 16 + MaxClassLen;

	    if ( Class(Case) != Predict )
	    {
//		printf("   [%s]", ClassName[Predict]);
		CurrentPosition += 5 + strlen(ClassName[Predict]);
	    }
	}
	else
	{
//	    printf("%-15.15s %-15.15s [%.2f]",
//		    ClassName[Class(Case)],
//		    ClassName[Predict], GCEnv->Confidence);
	    CurrentPosition = 54;
	}
	fprintf(out,"%s\n",ClassName[Predict]);

	if ( RULESUSED ) ShowRules(StartList - CurrentPosition);

//	printf("\n");

	/*  Free the memory used by this case  */

	FreeLastCase(Case);
    }

    /*  Close the case file and free allocated memory  */

    fclose(F);
    fclose(out);
    FreeGlobals();

    return 0;
}



/*************************************************************************/
/*									 */
/*	Show rules that were used to classify a case.			 */
/*	Classify() will have set GCEnvRulesUsed[] to			 */
/*	  number of active rules for trial 0,				 */
/*	  first active rule, second active rule, ..., last active rule,	 */
/*	  number of active rules for trial 1,				 */
/*	  first active rule, second active rule, ..., last active rule,	 */
/*	and so on.							 */
/*									 */
/*************************************************************************/


void ShowRules(int Spaces)
/*   ---------  */
{
    int	p, pLast, a, b, First;

    printf("%*s", Spaces, "");

    p = 0;
    ForEach(Trial, 0, TRIALS-1)
    {
	pLast = p + GCEnv->RulesUsed[p];

	ForEach(a, 1, GCEnv->RulesUsed[p])
	{
	    /*  Rules used are not in order, so find first  */

	    First = 0;

	    ForEach(b, p+1, pLast)
	    {
		if ( GCEnv->RulesUsed[b] &&
		     ( ! First ||
		       GCEnv->RulesUsed[b] < GCEnv->RulesUsed[First] ) )
		{
		    First = b;
		}
	    }

	    if ( TRIALS > 1 ) printf("%d/", Trial);

	    printf("%d ", GCEnv->RulesUsed[First]);

	    GCEnv->RulesUsed[First] = 0;
	}

	p = pLast + 1;
    }
}
