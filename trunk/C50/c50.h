#ifndef C50_H
#define C50_H
#include "defns.h"

class C50{
public:
    double StartTime;
	int		VERBOSITY,
			TRIALS,
			FOLDS,
			UTILITY,
			NCPU;

	Boolean		SUBSET,
			BOOST,
			PROBTHRESH,
			RULES,
			XVAL,
			NOCOSTS,
			WINNOW,
			GLOBAL;

	CaseCount	MINITEMS,
			LEAFRATIO;

	float		CF,
			SAMPLE;

	Boolean		LOCK;

	Attribute	ClassAtt,
			LabelAtt,
			CWtAtt;

 double		AvCWt;

	String		*ClassName,
			*AttName,
			**AttValName;

	char 		*IgnoredVals;
	int		IValsSize,
			IValsOffset;

	int		MaxAtt,
			MaxClass,
			MaxDiscrVal,
			MaxLabel,
			LineNo,
			ErrMsgs,
			AttExIn,
			TSBase;

	DiscrValue	*MaxAttVal;

	char		*SpecialStatus;

	Definition	*AttDef;
	Attribute	**AttDefUses;

	Boolean		*SomeMiss,
			*SomeNA,
			Winnowed;

	ContValue	*ClassThresh;

	CaseNo		MaxCase;

	DataRec		*Case;

	DataRec		*SaveCase;

	String		FileStem;

	Tree		*Raw,
			*Pruned,
			WTree;

	float		Confidence,
			SampleFrac,
			*Vote,
			*BVoteBlock,
			**MCost,
			**NCost,
			*WeightMul;

	CRule		*MostSpec;

	Boolean		UnitWeights,
			CostWeights;

	int		Trial,
			MaxTree;

	ClassNo		*TrialPred;

 double		*ClassFreq,
			**DFreq;

	float		*Gain,
			*Info,
			*EstMaxGR,
			*ClassSum;

	ContValue	*Bar;

	double		GlobalBaseInfo,
			**Bell;

	Byte		*Tested;

	Set		**Subset;
	int		*Subsets;

	EnvRec		GEnv;

	CRule		*Rule;

	RuleNo		NRules,
			RuleSpace;

	CRuleSet	 *RuleSet;

	ClassNo		Default;

	Byte		**Fires,
			*CBuffer;

	int		*CovBy,
			*List;

	float		AttTestBits,
			*BranchBits;
	int		*AttValues,
			*PossibleCuts;

	double		*LogCaseNo,
			*LogFact;

	int		*UtilErr,
			*UtilBand;
	double		*UtilCost;

	int		KRInit,
			Now;

	FILE		*TRf;
	char		Fn[500];

	FILE  		*Of;
	public:
	void	ConstructClassifiers(void);
void	    InitialiseWeights(void);
void	    SetAvCWt(void);
void	    Evaluate(int Flags);
void	    EvaluateSingle(int Flags);
void	    EvaluateBoost(int Flags);
void	    RecordAttUsage(DataRec Case, int *Usage);
Boolean	    ReadName(FILE *f, String s, int n, char ColonOpt);
void	    GetNames(FILE *Nf);
void	    ExplicitAtt(FILE *Nf);
int	    Which(String Val, String *List, int First, int Last);
void	    ListAttsUsed(void);
void	    FreeNames(void);
int	    InChar(FILE *f);
void	    ImplicitAtt(FILE *Nf);
void	    ReadDefinition(FILE *f);
void	    Append(char c);
Boolean	    Expression(void);
Boolean	    Conjunct(void);
Boolean	    SExpression(void);
Boolean	    AExpression(void);
Boolean	    Term(void);
Boolean	    Factor(void);
Boolean	    Primary(void);
Boolean	    Atom(void);
Boolean	    Find(String S);
int	    FindOne(String *Alt);
Attribute   FindAttName(void);
void	    DefSyntaxError(String Msg);
void	    DefSemanticsError(int Fi, String Msg, int OpCode);
void	    Dump(char OpCode, ContValue F, String S, int Fi);
void	    DumpOp(char OpCode, int Fi);
Boolean	    UpdateTStack(char OpCode, ContValue F, String S, int Fi);
AttValue    EvaluateDef(Definition D, DataRec Case);
void	    GetData(FILE *Df, Boolean Train, Boolean AllowUnknownClass);
DataRec	    GetDataRec(FILE *Df, Boolean Train);
CaseNo	    CountData(FILE *Df);
int	    StoreIVal(String s);
void	    FreeData(void);
void	    CheckValue(DataRec Case, Attribute Att);
void	    GetMCosts(FILE *f);
void	    WinnowAtts(void);
float	    TrialTreeCost(Boolean FirstTime);
float	    ErrCost(Tree T, CaseNo Fp, CaseNo Lp);
void	    ScanTree(Tree T, Boolean *Used);
void	    InitialiseTreeData(void);
void	    FreeTreeData(void);
void	    SetMinGainThresh(void);
void	    FormTree(CaseNo, CaseNo, int, Tree *);
void	    SampleEstimate(CaseNo Fp, CaseNo Lp, CaseCount Cases);
void	    Sample(CaseNo Fp, CaseNo Lp, CaseNo N);
Attribute   ChooseSplit(CaseNo Fp, CaseNo Lp, CaseCount Cases, Boolean Sampled);
void	    ProcessQueue(CaseNo WFp, CaseNo WLp, CaseCount WCases);
Attribute   FindBestAtt(CaseCount Cases);
void	    EvalDiscrSplit(Attribute Att, CaseCount Cases);
CaseNo	    Group(DiscrValue, CaseNo, CaseNo, Tree);
CaseCount   SumWeights(CaseNo, CaseNo);
CaseCount   SumNocostWeights(CaseNo, CaseNo);
void	    FindClassFreq(double [], CaseNo, CaseNo);
void	    FindAllFreq(CaseNo, CaseNo);
void	    Divide(Tree Node, CaseNo Fp, CaseNo Lp, int Level);
void	    EvalDiscreteAtt(Attribute Att, CaseCount Cases);
void	    EvalOrderedAtt(Attribute Att, CaseCount Cases);
void	    SetDiscrFreq(Attribute Att);
double	    DiscrKnownBaseInfo(CaseCount KnownCases, DiscrValue MaxVal);
void	    DiscreteTest(Tree Node, Attribute Att);
void	    EvalContinuousAtt(Attribute Att, CaseNo Fp, CaseNo Lp);
void	    EstimateMaxGR(Attribute Att, CaseNo Fp, CaseNo Lp);
void	    PrepareForContin(Attribute Att, CaseNo Fp, CaseNo Lp);
CaseNo	    PrepareForScan(CaseNo Lp);
void	    ContinTest(Tree Node, Attribute Att);
void	    AdjustAllThresholds(Tree T);
void	    AdjustThresholds(Tree T, Attribute Att, CaseNo *Ep);
ContValue   GreatestValueBelow(ContValue Th, CaseNo *Ep);
double	    ComputeGain(double BaseInfo, float UnknFrac, DiscrValue MaxVal,
			CaseCount TotalCases);
double	    TotalInfo(double V[], DiscrValue MinVal, DiscrValue MaxVal);
void	    PrintDistribution(Attribute Att, DiscrValue MinVal,
			DiscrValue MaxVal, double **Freq, double *ValFreq,
			Boolean ShowNames);
			void	    InitialiseBellNumbers(void);
void	    EvalSubset(Attribute Att, CaseCount Cases);
void	    Merge(DiscrValue x, DiscrValue y, CaseCount Cases);
void	    EvaluatePair(DiscrValue x, DiscrValue y, CaseCount Cases);
void	    PrintSubset(Attribute Att, Set Ss);
void	    SubsetTest(Tree Node, Attribute Att);
Boolean	    SameDistribution(DiscrValue V1, DiscrValue V2);
void	    AddBlock(DiscrValue V1, DiscrValue V2);
void	    MoveBlock(DiscrValue V1, DiscrValue V2);
void	    Prune(Tree T);
void	    EstimateErrs(Tree T, CaseNo Fp, CaseNo Lp, int Sh, int Flags);
void	    GlobalPrune(Tree T);
void	    FindMinCC(Tree T);
void	    InsertParents(Tree T, Tree P);
void	    CheckSubsets(Tree T, Boolean);
void	    InitialiseExtraErrs(void);
float	    ExtraErrs(CaseCount N, CaseCount E, ClassNo C);
float	    RawExtraErrs(CaseCount N, CaseCount E);
void	    RestoreDistribs(Tree T);
void	    CompressBranches(Tree T);
void	    SetGlobalUnitWeights(int LocalFlag);
void	    SoftenThresh(Tree T);
void	    ResubErrs(Tree T, CaseNo Fp, CaseNo Lp);
void	    FindBounds(Tree T, CaseNo Fp, CaseNo Lp);
ClassNo	    TreeClassify(DataRec Case, Tree DecisionTree);
void	    FollowAllBranches(DataRec Case, Tree T, float Fraction);
ClassNo	    RuleClassify(DataRec Case, CRuleSet RS);
int	    FindOutcome(DataRec Case, Condition OneCond);
Boolean	    Matches(CRule R, DataRec Case);
void	    CheckActiveSpace(int N);
void	    MarkActive(RuleTree RT, DataRec Case);
void	    SortActive(void);
void	    CheckUtilityBand(int *u, RuleNo r, ClassNo Actual, ClassNo Default);
ClassNo	    BoostClassify(DataRec Case, int MaxTrial);
ClassNo	    SelectClass(ClassNo Default, Boolean UseCosts);
ClassNo	    Classify(DataRec Case);
float	    Interpolate(Tree T, ContValue Val);
void	    FindLeaf(DataRec Case, Tree T, Tree PT, float Wt);
Boolean	    Satisfies(DataRec Case, Condition OneCond);

void	    Quicksort(CaseNo Fp, CaseNo Lp, Attribute Att);
void	    Cachesort(CaseNo Fp, CaseNo Lp, SortRec *SRec);
void	    FindDepth(Tree T);
void	    PrintTree(Tree T, String Title);
void	    Show(Tree T, int Sh);
void	    ShowBranch(int Sh, Tree T, DiscrValue v, DiscrValue BrNo);
DiscrValue  Elements(Attribute Att, Set S, DiscrValue *Last);
int	    MaxLine(Tree SubTree);
void	    Indent(int Sh, int BrNo);
void	    FreeTree(Tree T);
Tree	    Leaf(double *Freq, ClassNo NodeClass, CaseCount Cases,
		 CaseCount Errors);
void	    Sprout(Tree T, DiscrValue Branches);
void	    UnSprout(Tree T);
int	    TreeSize(Tree T);
int	    ExpandedLeafCount(Tree T);
int	    TreeDepth(Tree T);
Tree	    CopyTree(Tree T);
void	    PrintHeader(String Title);
char	    ProcessOption(int Argc, char **Argv, char *Str);
void	    *Pmalloc(size_t Bytes);
void	    *Prealloc(void *Present, size_t Bytes);
void	    *Pcalloc(size_t Number, unsigned int Size);
void	    FreeVector(void **V, int First, int Last);
DataRec	    NewCase(void);
void	    FreeCases(void);
void	    FreeLastCase(DataRec Case);
double	    KRandom(void);
void	    ResetKR(int KRInit);
void	    Error(int ErrNo, String S1, String S2);
String	    CaseLabel(CaseNo N);
FILE *	    GetFile(String Extension, String RW);
double	    ExecTime(void);
int	    Denominator(ContValue Val);
int	    GetInt(String S, int N);
int	    DateToDay(String DS);
void	    DayToDate(int DI, String Date);
int	    TimeToSecs(String TS);
void	    SecsToTime(int Secs, String Time);
void	    SetTSBase(int y);
int	    TStampToMins(String TS);
void	    Check(float Val, float Low, float High);
void	    CValToStr(ContValue CV, Attribute Att, String DS);
void	    Cleanup(void);
#ifdef UTF8
int	    UTF8CharWidth(unsigned char *U);
int	    wcwidth(wchar_t ucs);
int	    wcswidth(const wchar_t *pwcs, size_t n);
#endif
void	    PrintConfusionMatrix(CaseNo *ConfusionMat);
void	    PrintErrorBreakdown(CaseNo *ConfusionMat);
void	    PrintUsageInfo(CaseNo *Usage);
CRuleSet    FormRules(Tree T);
void	    Scan(Tree T);
void	    SetupNCost(void);
void	    PushCondition(void);
void	    PopCondition(void);
void	    PruneRule(Condition Cond[], ClassNo TargetClass);
void	    ProcessLists(void);
void	    AddToList(CaseNo *List, CaseNo N);
void	    DeleteFromList(CaseNo *Before, CaseNo N);
int	    SingleFail(CaseNo i);
void	    Increment(int d, CaseNo i, double *Total, double *Errors);
void	    FreeFormRuleData(void);
Boolean	    NewRule(Condition Cond[], int NConds, ClassNo TargetClass,
		    Boolean *Deleted, CRule Existing,
		    CaseCount Cover, CaseCount Correct, float Prior);
void	    ListSort(int *L, int Fp, int Lp);
Byte	    *Compress(int *L);
void	    Uncompress(Byte *CL, int *UCL);
Boolean	    SameRule(RuleNo r, Condition Cond[], int NConds,
		     ClassNo TargetClass);
void	    FreeRule(CRule R);
void	    FreeRules(CRuleSet RS);
void	    PrintRules(CRuleSet, String);
void	    PrintRule(CRule R);
void	    PrintCondition(Condition C);
void	    SiftRules(float EstErrRate);
void	    InvertFires(void);
void	    FindTestCodes(void);
float	    CondBits(Condition C);
void	    SetInitialTheory(void);
void	    CoverClass(ClassNo Target);
int	    MessageLength(RuleNo NR, double RuleBits, float Errs);
void	    HillClimb(void);
void	    InitialiseVotes(void);
void	    CountVotes(CaseNo i);
void	    UpdateDeltaErrs(CaseNo i, double Delta, RuleNo Toggle);
CaseCount   CalculateDeltaErrs(void);
void	    PruneSubsets(void);
void	    SetDefaultClass(void);
void	    SwapRule(RuleNo A, RuleNo B);
int	    OrderByUtility(void);
int	    OrderByClass(void);
void	    OrderRules(void);
void	    GenerateLogs(int MaxN);
void	    FreeSiftRuleData(void);

	/* ruletree.c */

void	    ConstructRuleTree(CRuleSet RS);
void	    SetTestIndex(Condition C);
RuleTree    GrowRT(RuleNo *RR, int RRN, CRule *Rule);
int	    DesiredOutcome(CRule R, int TI);
int	    SelectTest(RuleNo *RR, int RRN, CRule *Rule);
void	    FreeRuleTree(RuleTree RT);

	/* modelfiles.c */

void	    CheckFile(String Extension, Boolean Write);
void	    WriteFilePrefix(String Extension);
void	    ReadFilePrefix(String Extension);
void	    SaveDiscreteNames(void);
void	    SaveTree(Tree T, String Extension);
void	    OutTree(Tree T);
void	    SaveRules(CRuleSet RS, String Extension);
void	    AsciiOut(String Pre, String S);
void	    ReadHeader(void);
Tree	    GetTree(String Extension);
Tree	    InTree(void);
CRuleSet    GetRules(String Extension);
CRuleSet    InRules(void);
CRule	    InRule(void);
Condition   InCondition(void);
int	    ReadProp(char *Delim);
String	    RemoveQuotes(String S);
Set	    MakeSubset(Attribute Att);
void	    StreamIn(String S, int n);

	/* update.c (Unix) or winmain.c (WIN32) */

void	    NotifyStage(int);
void	    Progress(float);

	/* xval.c */

void	    CrossVal(void);
void	    Prepare(void);
void	    Shuffle(int *Vec);
void	    Summary(void);
float	    SE(float sum, float sumsq, int no);
void FreeClassifier(int Trial);
C50(){
		VERBOSITY=0,	/* verbosity level (0 = none) */
		TRIALS=1,	/* number of trees to be grown */
		FOLDS=10,	/* crossvalidation folds */
		UTILITY=0;	/* rule utility bands */

		SUBSET=0,	/* subset tests allowed */
		BOOST=0,	/* boosting invoked */
		PROBTHRESH=0,	/* to use soft thresholds */
		RULES=0,	/* rule-based classifiers */
		XVAL=0,		/* perform crossvalidation */
		NOCOSTS=0,	/* ignoring costs */
		WINNOW=0,	/* attribute winnowing */
		GLOBAL=1;	/* use global pruning for trees */

	MINITEMS=2,	/* minimum cases each side of a cut */
		LEAFRATIO=0;	/* leaves per case for boosting */

		/* confidence limit for tree pruning */
		SAMPLE=0.0;	/* sample training proportion */

	LOCK=false;	/* sample locked */

	ClassAtt=0,	/* attribute to use as class */
		LabelAtt=0,	/* attribute to use as case ID */
		CWtAtt=0;	/* attribute to use for case weight */

		AvCWt;		/* average case weight */

		ClassName=0,	/* class names */
		AttName=0,	/* att names */
		AttValName=0;	/* att value names */

		IgnoredVals=0;	/* values of labels and atts marked ignore */
		IValsSize=0,	/* size of above */
		IValsOffset=0;	/* index of first free char */

		MaxAtt,		/* max att number */
		MaxClass,	/* max class number */
		MaxDiscrVal=3,	/* max discrete values for any att */
		MaxLabel=0,	/* max characters in case label */
		LineNo=0,	/* input line number */
		ErrMsgs=0,	/* errors found */
		AttExIn=0,	/* attribute exclusions/inclusions */
		TSBase=0;	/* base day for time stamps */

	MaxAttVal=0;	/* number of values for each att */

		SpecialStatus=0;/* special att treatment */

	AttDef=0;	/* definitions of implicit atts */
	AttDefUses=0;	/* list of attributes used by definition */

		SomeMiss=Nil,	/* att has missing values */
		SomeNA=Nil,	/* att has N/A values */
		Winnowed=0;	/* atts have been winnowed */

	ClassThresh=0;	/* thresholded class attribute */

		MaxCase=-1;	/* max data case number */

		Case=0;	/* data cases */

		SaveCase=0;

		FileStem="undefined";

		Raw=0,		/* unpruned trees */
		Pruned=0,	/* pruned trees */
		WTree=0;	/* winnow tree */

		Confidence,	/* set by classify() */
		SampleFrac=1,	/* fraction used when sampling */
		Vote=0,	/* total votes for classes */
		BVoteBlock=0,	/* boost voting block */
		MCost=0,	/* misclass cost [pred][real] */
		NCost=0,	/* normalised MCost used for rules */
		WeightMul=0;	/* prior adjustment factor */

		MostSpec=0;	/* most specific rule for each class */

		UnitWeights=1,	/* all weights are 1.0 */
		CostWeights=0;	/* reweight cases for costs */

		Trial,		/* trial number for boosting */
		MaxTree=0;	/* max tree grown */

		TrialPred=0;	/* predictions for each boost trial */

		ClassFreq=0,	/* ClassFreq[c] = # cases of class c */
		DFreq=0;	/* DFreq[a][c*x] = Freq[][] for attribute a */

		Gain=0,	/* Gain[a] = info gain by split on att a */
		Info=0,	/* Info[a] = max info from split on att a */
		EstMaxGR=0,	/* EstMaxGR[a] = est max GR from folit on a */
		ClassSum=0;	/* class weights during classification */

	Bar=0;		/* Bar[a]  = best threshold for contin att a */

		GlobalBaseInfo,	/* base information before split */
		Bell=0;	/* table of Bell numbers for subsets */

		Tested=0;	/* Tested[a] = att a already tested */

		Subset=0;	/* Subset[a][s] = subset s for att a */
		Subsets=0;	/* Subsets[a] = no. subsets for att a */

		GEnv;		/* environment block */

		Rule=0;	/* current rules */

		NRules,		/* number of rules */
		RuleSpace;	/* space currently allocated for rules */

	RuleSet=0;	/* rulesets */

		Default;	/* default class associated with ruleset or
				   boosted classifier */

		Fires=Nil,	/* Fires[r][*] = cases covered by rule r */
		CBuffer=Nil;	/* buffer for compressing lists */

		CovBy=Nil,	/* entry numbers for Fires inverse */
		List=Nil;	/* temporary list of cases or rules */

		AttTestBits,	/* average bits to encode tested attribute */
		BranchBits=0;	/* ditto attribute value */
		AttValues=0,	/* number of attribute values in the data */
		PossibleCuts=0;/* number of thresholds for an attribute */

		LogCaseNo=0,	/* LogCaseNo[i] = log2(i) */
		LogFact=0;	/* LogFact[i] = log2(i!) */

		UtilErr=0,	/* error by utility band */
		UtilBand=0;	/* last rule in each band */
		UtilCost=0;	/* cost ditto */

		KRInit=0,	/* KRandom initializer for SAMPLE */
		Now=0;		/* current stage */

		TRf=0;		/* file pointer for tree and rule i/o */
		Fn[500];	/* file name */

 		Of=0;		/* output file */
                
StartTime  = ExecTime();

}
void alocar(){
    Of = stdout;
    NotifyStage(READDATA);
    Progress(-1.0);
    
    if ( ! BOOST )
    {
	TRIALS = 1;
    }
    SpecialStatus = AllocZero(MaxAtt+1, char);
    SomeMiss = AllocZero(MaxAtt+1, Boolean);
SomeNA   = AllocZero(MaxAtt+1, Boolean);
if ( RULES )
    {
        int a= TRIALS;

	RuleSet = AllocZero(a, CRuleSet);
    }
}
void setCF(float cf){
    CF = cf;
}
void imprimir(){
    int i,j;
    for(i=0; i< MaxAtt; i++){
        printf("%s\n",AttName[i]);
    }
   
    for(i=0; i<MaxAtt;i++){
        printf("\n\n %d \n\n",MaxAttVal[i]);
        for(j=0; j<MaxAttVal[i];j++){
             printf("%s\n",AttValName[i][j]);
        }
        
    }
   
    
}
};
#endif 