#ifndef ALICALOTRACKREADER_H
#define ALICALOTRACKREADER_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice     */
/* $Id:  $ */

//_________________________________________________________________________
// Base class for reading data: MonteCarlo, ESD or AOD, of PHOS EMCAL and 
// Central Barrel Tracking detectors.
// Not all MC particles/tracks/clusters are kept, some kinematical restrictions are done.
// Mother class of : AliCaloTrackESDReader: Fills ESD data in 3 TObjArrays (PHOS, EMCAL, CTS)
//                 : AliCaloTrackMCReader: Fills Kinematics data in 3 TObjArrays (PHOS, EMCAL, CTS)
//                 : AliCaloTrackAODReader: Fills AOD data in 3 TObjArrays (PHOS, EMCAL, CTS) 
//  
// This part is commented: Mixing analysis can be done, input AOD with events
// is opened in the AliCaloTrackReader::Init()

// -- Author: Gustavo Conesa (INFN-LNF)

// --- ROOT system ---
#include "TObject.h" 
#include "TString.h"
#include "TRandom3.h"
class TObjArray ; 
class TTree ;

//--- ANALYSIS system ---
#include "AliVCaloCells.h"
class AliStack ; 
class AliHeader ; 
class AliGenEventHeader ; 
#include "AliVEvent.h"
class AliAODEvent;
class AliMCEvent;
class AliMixedEvent;
class AliAODMCHeader;
class AliESDtrackCuts;
class AliCentrality;
class AliTriggerAnalysis;
class AliEventplane;

// --- PartCorr
#include "AliCalorimeterUtils.h"
#include "AliFiducialCut.h"

class AliCaloTrackReader : public TObject {

public: 
  AliCaloTrackReader() ; // ctor
  virtual ~AliCaloTrackReader() ;//virtual dtor
private:
  AliCaloTrackReader(const AliCaloTrackReader & g) ; // cpy ctor
  AliCaloTrackReader & operator = (const AliCaloTrackReader & g) ;//cpy assignment

public:
  
  //--------------------------------
  // General methods
  //--------------------------------

  virtual void    Init();
  virtual void    InitParameters();
  virtual void    Print(const Option_t * opt) const;
  virtual void    ResetLists();

  virtual Int_t   GetDebug()           const { return fDebug          ; }
  virtual void    SetDebug(Int_t d)          { fDebug = d             ; }
  
  enum inputDataType {kESD, kAOD, kMC};
  virtual Int_t   GetDataType()        const { return fDataType       ; }
  virtual void    SetDataType(Int_t data )   { fDataType = data       ; }

  virtual Int_t   GetEventNumber()     const { return fEventNumber    ; }
  //virtual TString GetCurrentFileName() const { return fCurrentFileName ; }
	
  TString         GetTaskName()        const { return fTaskName       ; }
  void            SetTaskName(TString name)  { fTaskName = name       ; }
    
  //---------------------------------------
  //Input/output event setters and getters
  //---------------------------------------
  virtual void    SetInputEvent(AliVEvent* const input) ;
  virtual void    SetOutputEvent(AliAODEvent* const aod) { fOutputEvent = aod ; }
  virtual void    SetMC(AliMCEvent* const mc)            { fMC          = mc  ; }
  virtual void    SetInputOutputMCEvent(AliVEvent* /*esd*/, AliAODEvent* /*aod*/, AliMCEvent* /*mc*/) { ; }
  
  // Delta AODs
  virtual TList * GetAODBranchList()      const { return fAODBranchList        ; }
  void    SetDeltaAODFileName(TString name )    { fDeltaAODFileName = name     ; }
  TString GetDeltaAODFileName()           const { return fDeltaAODFileName     ; }
  void    SwitchOnWriteDeltaAOD()               { fWriteOutputDeltaAOD = kTRUE ; }
  void    SwitchOffWriteDeltaAOD()              { fWriteOutputDeltaAOD = kFALSE; }
  Bool_t  WriteDeltaAODToFile()           const { return fWriteOutputDeltaAOD  ; } 
  
  //------------------------------------------------------------
  //Clusters/Tracks arrays filtering/filling methods and switchs 
  //------------------------------------------------------------
  
  //Minimum pt setters and getters 
  virtual Float_t  GetEMCALPtMin()        const { return fEMCALPtMin ; }
  virtual Float_t  GetPHOSPtMin()         const { return fPHOSPtMin  ; }
  virtual Float_t  GetCTSPtMin()          const { return fCTSPtMin   ; }
  virtual Float_t  GetEMCALPtMax()        const { return fEMCALPtMax ; }
  virtual Float_t  GetPHOSPtMax()         const { return fPHOSPtMax  ; }
  virtual Float_t  GetCTSPtMax()          const { return fCTSPtMax   ; }
  
  virtual void     SetEMCALPtMin(Float_t  pt)   { fEMCALPtMin = pt   ; }
  virtual void     SetPHOSPtMin(Float_t  pt)    { fPHOSPtMin  = pt   ; }
  virtual void     SetCTSPtMin(Float_t  pt)     { fCTSPtMin   = pt   ; }  
  
  virtual void     SetEMCALPtMax(Float_t  pt)   { fEMCALPtMax = pt   ; }
  virtual void     SetPHOSPtMax(Float_t  pt)    { fPHOSPtMax  = pt   ; }
  virtual void     SetCTSPtMax(Float_t  pt)     { fCTSPtMax   = pt   ; }  
  
  // Fidutial cuts  
  virtual AliFiducialCut * GetFiducialCut()     { if(!fFiducialCut) fFiducialCut = new AliFiducialCut(); 
                                                return  fFiducialCut ;}
  virtual void SetFiducialCut(AliFiducialCut * const fc) { fFiducialCut = fc ;}
  virtual Bool_t IsFiducialCutOn()        const { return fCheckFidCut   ; }
  virtual void SwitchOnFiducialCut()            { fCheckFidCut = kTRUE;  fFiducialCut = new AliFiducialCut();}
  virtual void SwitchOffFiducialCut()           { fCheckFidCut = kFALSE ; }
  
  // Cluster origin
  Bool_t IsEMCALCluster(AliVCluster *clus) const;
  Bool_t IsPHOSCluster (AliVCluster *clus) const;
  //Patch for cluster origin for Old AODs implementation
  void   SwitchOnOldAODs()              { fOldAOD = kTRUE          ; }
  void   SwitchOffOldAODs()             { fOldAOD = kFALSE         ; }
  
  // Cluster/track/cells switchs
  Bool_t IsCTSSwitchedOn()        const { return fFillCTS          ; }
  void   SwitchOnCTS()                  { fFillCTS = kTRUE         ; }
  void   SwitchOffCTS()                 { fFillCTS = kFALSE        ; }

  Bool_t IsEMCALSwitchedOn()      const { return fFillEMCAL        ; }
  void   SwitchOnEMCAL()                { fFillEMCAL = kTRUE       ; }
  void   SwitchOffEMCAL()               { fFillEMCAL = kFALSE      ; }

  Bool_t IsPHOSSwitchedOn()       const { return fFillPHOS         ; }
  void   SwitchOnPHOS()                 { fFillPHOS = kTRUE        ; }
  void   SwitchOffPHOS()                { fFillPHOS = kFALSE       ; }

  Bool_t IsEMCALCellsSwitchedOn() const { return fFillEMCALCells   ; }
  void   SwitchOnEMCALCells()           { fFillEMCALCells = kTRUE  ; }
  void   SwitchOffEMCALCells()          { fFillEMCALCells = kFALSE ; }

  Bool_t IsPHOSCellsSwitchedOn()  const { return fFillPHOSCells    ; }
  void   SwitchOnPHOSCells()            { fFillPHOSCells = kTRUE   ; }
  void   SwitchOffPHOSCells()           { fFillPHOSCells = kFALSE  ; }

  void   SwitchOnEmbeddedClustersSelection() { fSelectEmbeddedClusters = kTRUE   ; }
  void   SwitchOffEmbeddedClustersSelection(){ fSelectEmbeddedClusters = kFALSE  ; }
  
  // Filling/ filtering / detector information access methods
  virtual Bool_t FillInputEvent(const Int_t iEntry, const char *currentFileName)  ;
  virtual void   FillInputCTS() ;
  virtual void   FillInputEMCAL() ;
  virtual void   FillInputEMCALAlgorithm(AliVCluster * clus, const Int_t iclus) ;
  virtual void   FillInputPHOS() ;
  virtual void   FillInputEMCALCells() ;
  virtual void   FillInputPHOSCells() ;
  virtual void   FillInputVZERO() ;  
  
  Int_t          GetV0Signal(Int_t i)                    const { return fV0ADC[i] ; }
  Int_t          GetV0Multiplicity(Int_t i)              const { return fV0Mul[i] ; }
  
  void           SetEMCALClusterListName(TString &name) {fEMCALClustersListName = name ; }

  // Arrayes with clusters/track/cells access method
  virtual TObjArray*     GetCTSTracks()     const { return fCTSTracks     ; }
  virtual TObjArray*     GetEMCALClusters() const { return fEMCALClusters ; }
  virtual TObjArray*     GetPHOSClusters()  const { return fPHOSClusters  ; }
  virtual AliVCaloCells* GetEMCALCells()    const { return fEMCALCells    ; }
  virtual AliVCaloCells* GetPHOSCells()     const { return fPHOSCells     ; }

  //Methods for mixing with external input file (AOD)
  //virtual TTree* GetSecondInputAODTree() const {return  fSecondInputAODTree ; } 
  //virtual void SetSecondInputAODTree(TTree * tree) {fSecondInputAODTree = tree ;
  //												  fSecondInputAODEvent->ReadFromTree(tree);}//Connect tree and AOD event.
					
  //virtual AliAODEvent* GetSecondInputAODEvent() const { return fSecondInputAODEvent ; } 
	
  //TString GetSecondInputFileName() const    {return fSecondInputFileName ; }
  //void SetSecondInputFileName(TString name) { fSecondInputFileName = name ; }

  //Int_t GetSecondInputFirstEvent() const    {return fSecondInputFirstEvent ; }
  //void SetSecondInputFirstEvent(Int_t iEvent0) { fSecondInputFirstEvent = iEvent0 ; }	
	
//  Int_t GetAODCTSNormalInputEntries()   {if(!fSecondInputAODTree) { fAODCTSNormalInputEntries   = fAODCTS->GetEntriesFast()  ;}
//										 return fAODCTSNormalInputEntries ; }
//  Int_t GetAODEMCALNormalInputEntries() {if(!fSecondInputAODTree) { fAODEMCALNormalInputEntries = fAODEMCAL->GetEntriesFast();}
//										 return fAODEMCALNormalInputEntries ; }
//  Int_t GetAODPHOSNormalInputEntries()  {if(!fSecondInputAODTree) { fAODPHOSNormalInputEntries  = fAODPHOS->GetEntriesFast() ;}
//										 return fAODPHOSNormalInputEntries ; }
	
   
  //-------------------------------------
  // Event/track selection methods
  //-------------------------------------
  
  void    SetFiredTriggerClassName(TString name ) { fFiredTriggerClassName = name   ; }
  TString GetFiredTriggerClassName()        const { return fFiredTriggerClassName   ; }
  virtual TString GetFiredTriggerClasses()        { return ""                       ; } // look the ESD/AOD reader 
  
  void    SwitchOnEventSelection()                { fDoEventSelection = kTRUE       ; }
  void    SwitchOffEventSelection()               { fDoEventSelection = kFALSE      ; }
  Bool_t  IsEventSelectionDone()            const { return fDoEventSelection        ; } 
  
  void    SwitchOnV0ANDSelection()                { fDoV0ANDEventSelection = kTRUE  ; }
  void    SwitchOffV0ANDSelection()               { fDoV0ANDEventSelection = kFALSE ; }
  Bool_t  IsV0ANDEventSelectionDone()       const { return fDoV0ANDEventSelection   ; } 

  void    SwitchOnPrimaryVertexSelection()        { fUseEventsWithPrimaryVertex = kTRUE  ; }
  void    SwitchOffPrimaryVertexSelection()       { fUseEventsWithPrimaryVertex = kFALSE ; }
  Bool_t  IsPrimaryVertexSelectionDone()    const { return fUseEventsWithPrimaryVertex   ; } 
  
  
  
  // Track selection
  ULong_t GetTrackStatus()                  const {return fTrackStatus      ; }
  void    SetTrackStatus(ULong_t bit)             { fTrackStatus = bit      ; }		
	
  AliESDtrackCuts* GetTrackCuts()           const { return fESDtrackCuts    ; }
  void    SetTrackCuts(AliESDtrackCuts * cuts)    { fESDtrackCuts = cuts    ; }		  
  Int_t   GetTrackMultiplicity()            const { return fTrackMult       ; }
  Float_t GetTrackMultiplicityEtaCut()      const { return fTrackMultEtaCut ; }
  void    SetTrackMultiplicityEtaCut(Float_t eta) { fTrackMultEtaCut = eta  ; }		
  
  // Calorimeter specific and patches
  void    AnalyzeOnlyLED()                        { fAnaLED = kTRUE         ; }
  void    AnalyzeOnlyPhysics()                    { fAnaLED = kFALSE        ; }
  
  void    SwitchOnCaloFilterPatch()               { fCaloFilterPatch = kTRUE ; fFillCTS = kFALSE    ; }
  void    SwitchOffCaloFilterPatch()              { fCaloFilterPatch = kFALSE                       ; }
  Bool_t  IsCaloFilterPatchOn()             const { if(fDataType == kAOD) { return fCaloFilterPatch ; } 
                                                    else                  { return kFALSE           ; } }
  	
  //-------------------------------
  //Vertex methods
  //-------------------------------
  virtual void      GetVertex(Double_t v[3])        const ;
  virtual Double_t* GetVertex(const Int_t evtIndex) const { return fVertex[evtIndex]            ; }
  virtual void      GetVertex(Double_t vertex[3],   const Int_t evtIndex) const ;
  virtual void      FillVertexArray();
  virtual Bool_t    CheckForPrimaryVertex();
 // virtual void       GetSecondInputAODVertex(Double_t *) const {;}
  virtual Float_t   GetZvertexCut()                 const { return fZvtxCut                     ; } //cut on vertex position  
  virtual void      SetZvertexCut(Float_t zcut=10.)       { fZvtxCut=zcut                       ; } //cut on vertex position

  //------------------------
  // Centrality / Event Plane
  //------------------------
  virtual AliCentrality* GetCentrality()            const { return fInputEvent->GetCentrality() ; } //Look in AOD reader, different there
  virtual void      SetCentralityClass(TString name)      { fCentralityClass   = name           ; }
  virtual void      SetCentralityOpt(Int_t opt)           { fCentralityOpt     = opt            ; }
  virtual TString   GetCentralityClass()            const { return fCentralityClass             ; }
  virtual Int_t     GetCentralityOpt()              const { return fCentralityOpt               ; }
  virtual Int_t     GetEventCentrality()            const ;
  virtual void      SetCentralityBin(Int_t min, Int_t max) //Set the centrality bin to select the event. If used, then need to get percentile
                                                          { fCentralityBin[0]=min; fCentralityBin[1]=max;  
                                                           if(min>=0 && max > 0) fCentralityOpt = 100 ; }
  virtual Float_t GetCentralityBin(Int_t i)         const { if(i < 0 || i > 1) return 0 ; 
                                                            else return fCentralityBin[i]             ; }
  
  virtual AliEventplane* GetEventPlane()            const { return fInputEvent->GetEventplane()   ; }           
  virtual void           SetEventPlaneMethod(TString m)   { fEventPlaneMethod = m                 ; }
  virtual TString        GetEventPlaneMethod()      const { return fEventPlaneMethod              ; }

  //-------------------------------------
  // Other methods
  //-------------------------------------
  AliCalorimeterUtils * GetCaloUtils()            const { return fCaloUtils                       ; }
  void   SetCaloUtils(AliCalorimeterUtils * caloutils)  { fCaloUtils = caloutils                  ; }  
  
  //Use only for MC
  void    SwitchOnClusterEnergySmearing()               { fSmearClusterEnergy = kTRUE             ; }
  void    SwitchOffClusterEnergySmearing()              { fSmearClusterEnergy = kFALSE            ; }
  Bool_t  IsClusterEnergySmeared()                const { return fSmearClusterEnergy              ; }   
  void    SetSmearingParameters(Int_t i, Float_t param) { if(i < 3)fSmearClusterParam[i] = param  ; }
    
  virtual Double_t GetBField()                    const { return fInputEvent->GetMagneticField()  ; } 
  
  //------------------------------------------------
  // MC analysis specific methods
  //-------------------------------------------------
  
  //Kinematics and galice.root available 
  virtual AliStack*          GetStack()          const ;
  virtual AliHeader*         GetHeader()         const ;
  virtual AliGenEventHeader* GetGenEventHeader() const ;
  
  //Filtered kinematics in AOD	
  virtual TClonesArray*     GetAODMCParticles(Int_t input = 0) const ;
  virtual AliAODMCHeader*   GetAODMCHeader(Int_t input = 0)    const ;
	
  virtual AliVEvent*        GetInputEvent()  const { return fInputEvent  ; }
  virtual AliVEvent* GetOriginalInputEvent() const { return 0x0          ; }
  virtual AliAODEvent*      GetOutputEvent() const { return fOutputEvent ; }
  virtual AliMCEvent*       GetMC()          const { return fMC          ; }
  virtual AliMixedEvent*    GetMixedEvent()  const { return fMixedEvent  ; }
  virtual Int_t             GetNMixedEvent() const { return fNMixedEvent ; } 
  
  void   SwitchOnStack()                           { fReadStack          = kTRUE  ; }
  void   SwitchOffStack()                          { fReadStack          = kFALSE ; }
  void   SwitchOnAODMCParticles()                  { fReadAODMCParticles = kTRUE  ; }
  void   SwitchOffAODMCParticles()                 { fReadAODMCParticles = kFALSE ; }
  Bool_t ReadStack()                         const { return fReadStack            ; }
  Bool_t ReadAODMCParticles()                const { return fReadAODMCParticles   ; }
	
  //Select generated events, depending on comparison of pT hard and jets.
  virtual Bool_t  ComparePtHardAndJetPt() ;
  virtual Bool_t  IsPtHardAndJetPtComparisonSet()       const { return  fComparePtHardAndJetPt   ; }
  virtual void    SetPtHardAndJetPtComparison(Bool_t compare) { fComparePtHardAndJetPt = compare ; }	
  virtual Float_t GetPtHardAndJetFactor()               const { return  fPtHardAndJetPtFactor    ; }
  virtual void    SetPtHardAndJetPtFactor(Float_t factor)     { fPtHardAndJetPtFactor = factor   ; }		
  
  //MC reader methods, declared there to allow compilation, they are only used in the MC reader:
  
  virtual void AddNeutralParticlesArray(TArrayI & /*array*/)  { ; }  
  virtual void AddChargedParticlesArray(TArrayI & /*array*/)  { ; } 
  virtual void AddStatusArray(TArrayI & /*array*/)            { ; }
  
  virtual void SwitchOnPi0Decay()                             { ; } 
  virtual void SwitchOffPi0Decay()                            { ; } 
  virtual void SwitchOnStatusSelection()                      { ; }
  virtual void SwitchOffStatusSelection()                     { ; }
  virtual void SwitchOnOverlapCheck()                         { ; }
  virtual void SwitchOffOverlapCheck()                        { ; }
  virtual void SwitchOnOnlyGeneratorParticles()               { ; }
  virtual void SwitchOffOnlyGeneratorParticles()              { ; }

  virtual void SetEMCALOverlapAngle(Float_t /*angle*/)        { ; }
  virtual void SetPHOSOverlapAngle(Float_t /*angle*/)         { ; }

  
 protected:
  Int_t	           fEventNumber;    // Event number
  //TString          fCurrentFileName;// Current file name under analysis
  Int_t            fDataType ;      // Select MC:Kinematics, Data:ESD/AOD, MCData:Both
  Int_t            fDebug;          // Debugging level
  AliFiducialCut * fFiducialCut;    //! Acceptance cuts
  Bool_t           fCheckFidCut ;   // Do analysis for clusters in defined region         

  Bool_t           fComparePtHardAndJetPt;  // In MonteCarlo, jet events, reject fake events with wrong jet energy.
  Float_t          fPtHardAndJetPtFactor;   // Factor between ptHard and jet pT to reject/accept event.

  Float_t          fCTSPtMin;       // pT Threshold on charged particles 
  Float_t          fEMCALPtMin;     // pT Threshold on emcal clusters
  Float_t          fPHOSPtMin;      // pT Threshold on phos clusters
  Float_t          fCTSPtMax;       // pT Threshold on charged particles 
  Float_t          fEMCALPtMax;     // pT Threshold on emcal clusters
  Float_t          fPHOSPtMax;      // pT Threshold on phos clusters
  
  TList          * fAODBranchList ; //-> List with AOD branches created and needed in analysis  
  TObjArray      * fCTSTracks ;     //-> temporal array with tracks
  TObjArray      * fEMCALClusters ; //-> temporal array with EMCAL CaloClusters
  TObjArray      * fPHOSClusters ;  //-> temporal array with PHOS  CaloClusters
  AliVCaloCells  * fEMCALCells ;    //! temporal array with EMCAL CaloCells
  AliVCaloCells  * fPHOSCells ;     //! temporal array with PHOS  CaloCells

  AliVEvent      * fInputEvent;     //! pointer to esd or aod input
  AliAODEvent    * fOutputEvent;    //! pointer to aod output
  AliMCEvent     * fMC;             //! Monte Carlo Event Handler  

  Bool_t           fFillCTS;        // use data from CTS
  Bool_t           fFillEMCAL;      // use data from EMCAL
  Bool_t           fFillPHOS;       // use data from PHOS
  Bool_t           fFillEMCALCells; // use data from EMCAL
  Bool_t           fFillPHOSCells;  // use data from PHOS
  Bool_t           fSelectEmbeddedClusters;   // Use only simulated clusters that come from embedding.
  Bool_t           fSmearClusterEnergy;       // Smear cluster energy, to be done only for simulated data to match real data
  Float_t          fSmearClusterParam[3];     // Smearing parameters
  TRandom3         fRandom;                   // Random generator
  
//  TTree *        fSecondInputAODTree;    // Tree with second input AOD, for mixing analysis.	
//  AliAODEvent*   fSecondInputAODEvent;   //! pointer to second input AOD event.
//  TString        fSecondInputFileName;   // File with AOD data to mix with normal stream of data.
//  Int_t          fSecondInputFirstEvent; // First event to be considered in the mixing.
//	
//  Int_t          fAODCTSNormalInputEntries;   // Number of entries in CTS   in case of standard input, larger with mixing.
//  Int_t          fAODEMCALNormalInputEntries; // Number of entries in EMCAL in case of standard input, larger with mixing.
//  Int_t          fAODPHOSNormalInputEntries;  // Number of entries in PHOS  in case of standard input, larger with mixing.
	
  ULong_t          fTrackStatus        ; // Track selection bit, select tracks refitted in TPC, ITS ...
  AliESDtrackCuts *fESDtrackCuts       ; // Track cut  
  Int_t            fTrackMult          ; // Track multiplicity
  Float_t          fTrackMultEtaCut    ; // Track multiplicity eta cut
  Bool_t           fReadStack          ; // Access kine information from stack
  Bool_t	         fReadAODMCParticles ; // Access kine information from filtered AOD MC particles
	
  TString          fDeltaAODFileName   ; // Delta AOD file name
  TString          fFiredTriggerClassName; // Name of trigger event type used to do the analysis

  Bool_t           fAnaLED;              // Analyze LED data only.

  TString          fTaskName;            // Name of task that executes the analysis
	
  AliCalorimeterUtils * fCaloUtils ;     //  Pointer to CalorimeterUtils

  AliMixedEvent  * fMixedEvent  ;        //! mixed event object. This class is not the owner
  Int_t            fNMixedEvent ;        // number of events in mixed event buffer
  Double_t      ** fVertex      ;        //! vertex array 3 dim for each mixed event buffer
  
  Bool_t           fWriteOutputDeltaAOD; // Write the created delta AOD objects into file  
	Bool_t           fOldAOD;              // Old AODs, before revision 4.20
  
  Int_t            fV0ADC[2]    ;        // Integrated V0 signal
  Int_t            fV0Mul[2]    ;        // Integrated V0 Multiplicity

  Bool_t           fCaloFilterPatch;             // CaloFilter patch
  TString          fEMCALClustersListName;       // Alternative list of clusters produced elsewhere and not from InputEvent
  Float_t          fZvtxCut ;	                   // Cut on vertex position  
  Bool_t           fDoEventSelection;            // Select events depending on V0, pileup, vertex well reconstructed, at least 1 track ...
  Bool_t           fDoV0ANDEventSelection;       // Select events depending on V0, fDoEventSelection should be on
  Bool_t           fUseEventsWithPrimaryVertex ; // Select events with primary vertex
  AliTriggerAnalysis* fTriggerAnalysis;          // Access to trigger selection algorithm for V0AND calculation
  
  //Centrality/Event plane
  TString          fCentralityClass;     // Name of selected centrality class     
  Int_t            fCentralityOpt;       // Option for the returned value of the centrality, possible options 5, 10, 100
  Int_t            fCentralityBin[2];    // Minimum and maximum value of the centrality for the analysis
  TString          fEventPlaneMethod;    // Name of event plane method, by default "Q"
  
  ClassDef(AliCaloTrackReader,31)
} ;


#endif //ALICALOTRACKREADER_H


