#ifndef ALIHMPIDQACHECKER_H
#define ALIHMPIDQACHECKER_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */


/* $Id$ */

//
//  Checks the quality assurance. 
//  By comparing with reference data
//  Skeleton for HMPID
//


// --- ROOT system ---
class TFile ; 
class TH1F ; 
class TObjArray ; 

// --- Standard library ---

// --- AliRoot header files ---
#include "AliQACheckerBase.h"

class AliHMPIDQAChecker: public AliQACheckerBase {

public:
  AliHMPIDQAChecker() ;          // ctor
  virtual ~AliHMPIDQAChecker() ; // dtor
  
  virtual void Check(Double_t * test, AliQAv1::ALITASK_t index, TObjArray ** list, const AliDetectorRecoParam * recoParam) ;
  
  Double_t CheckEntries(TObjArray * list) const ;
  Double_t CheckRec(TObjArray *listrec, TObjArray *listref) const ;
  Double_t CheckSim(TObjArray *listsim, TObjArray *listref) const ;

  Double_t CheckRaw(Int_t specie, TObjArray* list);

  void    InitOnlineThresholds();
  void    PrintThresholds();
  
  
private:
  AliHMPIDQAChecker(const AliHMPIDQAChecker& qac) ; // cpy ctor   
  AliHMPIDQAChecker& operator= (const AliHMPIDQAChecker&); // Not implemented
  Bool_t        fNoReference ; //! flag telling if reference data hqve been found or not  
  TObjArray *   fQARefRec ;    //! Reference data from OCDB 
  
  Int_t         fHmpQaThr_NumberOfExcludedDDL;                //
  Int_t         fHmpQaThr_DataSizeLowerThreshold;             //
  Int_t         fHmpQaThr_DataSizeUpperThreshold;             //
  Float_t       fHmpQaThr_PadOccupancyLowerThreshold;         //
  Float_t       fHmpQaThr_PadOccupancyUpperThreshold;         //
  Int_t         fHmpQaThr_SectorGainLossWarningThreshold;     //
  Int_t         fHmpQaThr_SectorGainLossErrorThreshold;       //
  Float_t       fHmpQaThr_MissingPadFractionWarningThreshold; //
  Float_t       fHmpQaThr_MissingPadFractionErrorThreshold;   //
  Bool_t        fIsOnlineThr;                                 // 
  
  ClassDef(AliHMPIDQAChecker,2)  // description 

};

#endif // AliHMPIDQAChecker_H
