// @(#) $Id$

#ifndef ALIHLTDATATYPES_H
#define ALIHLTDATATYPES_H
/* This file is property of and copyright by the ALICE HLT Project        * 
 * ALICE Experiment at CERN, All rights reserved.                         *
 * See cxx source for full Copyright notice                               */

/** @file   AliHLTDataTypes.h
    @author Matthias Richter, Timm Steinbeck, Jochen Thaeder
    @date   
    @brief  Data type declaration for the HLT module.
*/

#include <string>
#include <string.h>
#include <cstdio>

//////////////////////////////////////////////////////////////////////////
//
// version no of HLT data types
//
//////////////////////////////////////////////////////////////////////////

/* Version   Description
 *   1       first version until June 07; implicite, not tagged
 *   2       introduced June 07, enhanced/cleaned/arranged structure
 *   3       2007-11-15 RAW DDL data type added; some inconsistencies fixed
 *           ('void' and 'any' origins); added signed HLT basic data types
 *           2007-11-23 origin defines have become variables in conjunction
 *           to be used with the operator| (AliHLTComponentDataType)
 *           2007-11-24 added trigger structs and ESD tree data type
 *   4       Component configuration and DCS update events added
 *           gkAliHLTDDLListSize set from 29 to 30 according to new PubSub
 *           specs
 *   5       Data types for Run and Event summary, and for monitoring added
 *   6       Common data types for TreeD and TreeR defined
 *           kAliHLTAllDataTypes and kAliHLTDataOriginSample added
 *           kAliHLTDataOriginEMCAL added
 *           kAliHLTDataTypeRunType added
 *   7       kAliHLTDataTypeComponentStatistics, kAliHLTDataTypeComponentTable,
 *           and AliHLTComponentStatistics have been added for optional
 *           component block statistics
 *   8       new wrapper interface has been introduced, old wrapper interface
 *           deprecated but kept for backward compatibility, the PubSub
 *           interface is going to be compiled independently of AliHLT, new
 *           interface provided by the libHLTinterface.so
 *           AliHLTComponentEnvironment -> AliHLTAnalysisEnvironment
 *   9       added data types for arrays of AliHLTExternalTrackParam sets and
 *           TClonesArrays of AliExternalTrackParam objects.
 *  10       Changes for information objects neededfor running with offline
 *           chains and analysis tasks.
 *           kAliHLTMCObjectDataType added
 *           kAliHLTDataOriginOffline added
 *           kAliHLTDataOriginHLT added
 *  11       extended AliHLTComponentStatistics: one more member to store the
 *           cycle time between events per component.
 *  12       added common data type id 'CLUSTERS'
 *           added data type 'ECSPARAM' for the full ECS parameter string to
 *           be sebt during SOR
 *           added kAliHLTDataTypeTrackMC (TRACK_MC) data type
 *           added data types (note: interface version stays the same
 *                 kAliHLTDataTypeDAQRDOUT (DAQRDOUT)
 *                 kAliHLTDataTypeTriggerDecision (TRIG_DEC)
 *                 kAliHLTDataTypeGlobalTrigger (GLOBTRIG)
 *                 kAliHLTDataTypeStreamerInfo (ROOTSTRI)
 *  13       Changed AliHLTEventDDL to now contain 31 words. The extra word is
 *           for the EMCAL detector, which needs 46 DDLs after DCAL was added.
 *  14       Adding new data block type for HLT global trigger counters.
 *           Adding data block type for ESD content
 *           Adding data block type for forwarded component table blocks
 *           Adding new event type for software triggers.
 *  15       Modifying data block types for trigger counter blocks.
 *  16       Adding data type for the meta data block to be forwarded by the
 *           TCPDumpSubscriber for the Common Data Header (CDH) and readout
 *           list information.
 *  17       New CDH v3 (10 32bit words, 100 trigger classes, etc.)
 *  18       Added AD detector in AliHLTEventDDLV2
 *  19       Added AD Component Data Types
 *  20       Add data type for ZMQ components and for internal custom triggers
 *  21       Add AliHLTDataTopic struct for ZMQ communication (as header).
 *  22       Add kAliHLTDataOriginPTR for passing pointers between threads
 *  23       Add Calo Trigger definitions
 *  24       Add CONFIG,INFO and CDBEntry data block types
 */
#define ALIHLT_DATA_TYPES_VERSION 23

//////////////////////////////////////////////////////////////////////////
//
// HLT data origin variables.
//
// By converting from defines to variables, the origins can be used with
// the operator|
//
// AliHLTComponentDataType dt;
// dt = kAliHLTDataTypeDDLRaw | kAliHLTDataOriginTPC;
//
//////////////////////////////////////////////////////////////////////////

/** field size of datat type origin 
 * @ingroup alihlt_component_datatypes
 */
const int kAliHLTComponentDataTypefOriginSize=4;


/** invalid data origin 
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTDataOriginVoid "\0\0\0"
/** old invalid data origin, kept for backward compatibility */
# define kAliHLTVoidDataOrigin "\0\0\0"

/** wildcard data type origin 
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTDataOriginAny "***"
/** old wildcard data type origin, kept for backward compatibility */
# define kAliHLTAnyDataOrigin "***"

/** Data origin HLT out 
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginOut[kAliHLTComponentDataTypefOriginSize];

/** Data origin HLT, used for HLT specifc data 
 *  in offline chains. This not a bug!
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginHLT[kAliHLTComponentDataTypefOriginSize];

/** Data origin Offline 
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginOffline[kAliHLTComponentDataTypefOriginSize];

/** Data origin HLT/PubSub private internal 
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginPrivate[kAliHLTComponentDataTypefOriginSize];

/** Data origin TPC 
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginTPC[kAliHLTComponentDataTypefOriginSize];

/** Data origin PHOS 
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginPHOS[kAliHLTComponentDataTypefOriginSize];

/** Data origin FMD
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginFMD[kAliHLTComponentDataTypefOriginSize];

/** Data origin MUON 
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginMUON[kAliHLTComponentDataTypefOriginSize];

/** Data origin TRD 
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginTRD[kAliHLTComponentDataTypefOriginSize];

/** Data origin ITS 
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginITS[kAliHLTComponentDataTypefOriginSize];

/** Data origin ITSOut 
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginITSOut[kAliHLTComponentDataTypefOriginSize];

/** Data origin ITS SPD
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginITSSPD[kAliHLTComponentDataTypefOriginSize];

/** Data origin ITS SDD
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginITSSDD[kAliHLTComponentDataTypefOriginSize];

/** Data origin ITS SSD
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginITSSSD[kAliHLTComponentDataTypefOriginSize];

/** Data origin for examples 
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginSample[kAliHLTComponentDataTypefOriginSize];

/** Data origin EMCAL 
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginEMCAL[kAliHLTComponentDataTypefOriginSize];

/** Data origin TOF
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginTOF[kAliHLTComponentDataTypefOriginSize];

/** Data origin HMPID
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginHMPID[kAliHLTComponentDataTypefOriginSize];

/** Data origin CPV
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginCPV[kAliHLTComponentDataTypefOriginSize];

/** Data origin PMD
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginPMD[kAliHLTComponentDataTypefOriginSize];

/** Data origin T0
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginT0[kAliHLTComponentDataTypefOriginSize];

/** Data origin VZERO
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginVZERO[kAliHLTComponentDataTypefOriginSize];

/** Data origin ZDC
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginZDC[kAliHLTComponentDataTypefOriginSize];

/** Data origin ACORDE
 * @ingroup alihlt_component_datatypes
 */

extern const char kAliHLTDataOriginACORDE[kAliHLTComponentDataTypefOriginSize];

/** Data origin TRG
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginTRG[kAliHLTComponentDataTypefOriginSize];

/** Data origin AD
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginAD[kAliHLTComponentDataTypefOriginSize];

/** Data origin pointer
 * for inter thread communication
 * @ingroup alihlt_component_datatypes
 */
extern const char kAliHLTDataOriginPTR[kAliHLTComponentDataTypefOriginSize];

//////////////////////////////////////////////////////////////////////////
//
// HLT common data type defines
//
//////////////////////////////////////////////////////////////////////////

/** field size of data type id 
 * @ingroup alihlt_component_datatypes
 */
const int kAliHLTComponentDataTypefIDsize=8;

/** field size of data type topic (ZMQ topic)
 * @ingroup alihlt_component_datatypes
 */
const int kAliHLTComponentDataTypeTopicSize =
        kAliHLTComponentDataTypefIDsize+kAliHLTComponentDataTypefOriginSize;

/** invalid data type id 
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTVoidDataTypeID "\0\0\0\0\0\0\0"

/** special id for all data types: any + void
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTAllDataTypesID "ALLDATA"

/** special id for any valid data type id
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTAnyDataTypeID "*******"

/** DDL RAW data 
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTDDLRawDataTypeID   {'D','D','L','_','R','A','W',' '}

/** CLUSTERS data
 * Common data type for the output of cluster finders, the exact
 * format depends on the origin (detector)
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTClustersDataTypeID {'C','L','U','S','T','E','R','S'}

/** calibration data for file exchange subscriber 
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTFXSCalibDataTypeID {'F','X','S','_','C','A','L',' '}

/** start of run (SOR) event 
 * @ref AliHLTRunDesc
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTSORDataTypeID      {'S','T','A','R','T','O','F','R'}

/** end of run (EOR) event 
 * @ref AliHLTRunDesc
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTEORDataTypeID      {'E','N','D','O','F','R','U','N'}

/** run type data block
 * string with run type as payload
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTRunTypeDataTypeID  {'R','U','N','T','Y','P','E',' '}

/** DDL list event 
 * @ref AliHLTEventDDL
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTDDLDataTypeID      {'D','D','L','L','I','S','T',' '}

/** DAQ readout list 
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTDAQRDOUTDataTypeID "DAQRDOUT"

/** HLT readout list.
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTReadoutListDataTypeID {'H','L','T','R','D','L','S','T'}

/** EventType event 
 * - empty payload, specification gives eventType
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTEventDataTypeID    {'E','V','E','N','T','T','Y','P'}

/** ECS parameter event 
 * - sent during the SOR event by the framework
 * - contains the full ECS parameter string
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTECSParamDataTypeID {'E','C','S','P','A','R','A','M'}

/** ComponentConfiguration event
 * - payload contains the CDB path as string
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTComConfDataTypeID  {'C','O','M','_','C','O','N','F'}

/** Direct ComponentConfiguration event
 * - payload contains the configuration string
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTConfigDataTypeID  {'C','O','N','F','I','G','_','_'}

/** Information string
 * - payload contains an information string
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTInfoDataTypeID  {'I','N','F','O','_','_','_','_'}

/** CDB entry
 * - payload contains the ROOT object containing the CDB entry
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTCDBEntryDataTypeID  {'C','D','B','E','N','T','R','Y'}

/** DCS value update event
 * - payload contains string of relevant detectors
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTUpdtDCSDataTypeID  {'U','P','D','T','_','D','C','S'}

/** MC data block
 * an AliMCEvent object of varying origin
 * The 'V0' at the end allows a versioning
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTMCObjectDataTypeID    {'A','L','I','M','C','_','V','0'}

/** ESDVertex data block
 * an AliESDVertex object of varying origin
 * The 'V0' at the end allows a versioning
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTESDVertexDataTypeID    {'E','S','D','V','T','X','V','0'}

/** KFVertex data block
 * an AliKFVertex object of varying origin
 * The 'V0' at the end allows a versioning
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTKFVertexDataTypeID    {'A','L','I','K','F','V','V','0'}


/** output of the GlobalVertexer data block
 * The 'V0' at the end allows a versioning
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTDataTypeGlobalVertexerID    {'G','L','B','V','T','X','V','0'}

/** output of the PrimaryFinder data block
 * The 'V0' at the end allows a versioning
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTDataTypePrimaryFinderID    {'P','R','I','V','T','X','V','0'}

/** output of the V0Finder data block
 * The 'V0' at the end allows a versioning
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTDataTypeV0FinderID    {'V','0','S','V','T','X','V','0'}

/** ESD data block
 * an AliESD object of varying origin
 * The 'V0' at the end allows a versioning
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTESDObjectDataTypeID    {'A','L','I','E','S','D','V','0'}

/** ESD friend data block
 * an AliESDfriend object of varying origin
 * The 'V0' at the end allows a versioning
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTESDfriendObjectDataTypeID    {'E','S','D','F','R','N','D','0'}

/** Flat ESD Vertex data block
 * The '0' at the end allows a versioning
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTFlatESDVertexDataTypeID    {'F','L','A','T','V','T','X','0'}

/** Flat ESD data block
 * an AliFlatESD object of varying origin
 * The '0' at the end allows a versioning
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTFlatESDDataTypeID    {'F','L','A','T','E','S','D','0'}

/** Flat ESD data block
 * an AliFlatESDFriend object of varying origin
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTFlatESDFriendDataTypeID    {'F','L','A','T','F','R','N','D'}

/** ESD 
 * data blocks designated for the ESD
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTESDContentDataTypeID   {'E','S','D','_','C','O','N','T'}

/** ESD 
 * data blocks designated for the ESD
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTESDFriendContentDataTypeID   {'F','R','N','D','C','O','N','T'}

/** ESD tree data block
 * TTree with an AliESD object of varying origin
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTESDTreeDataTypeID      {'E','S','D','_','T','R','E','E'}

/** AliRoot TreeD
 * - the digits tree of an AliRoot module
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTTreeDDataTypeID         {'A','L','I','T','R','E','E','D'}

/** AliRoot TreeR
 * - the rec points tree of an AliRoot module
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTTreeRDataTypeID         {'A','L','I','T','R','E','E','R'}

/** HW Address selection data block
 * - a selection list for 16 bit HW addresses
 * - varying origin
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTHwAddr16DataTypeID     {'H','W','A','D','D','R','1','6'}

/** Event Statistics
 * - event statistics for given detectors
 * - varying origin
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTEventStatisticsDataTypeID     {'E','V','_','S','T','A','T','I'}

/** Event Summary
 * - event summary
 * - origin : kAliHLTDataOriginOut ( HLT )
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTEventSummaryDataTypeID        {'E','V','_','S','U','M','M','A'}

/** Run Statistics
 * - run statistics for given detectors
 * - varying origin
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTRunStatisticsDataTypeID       {'R','U','N','S','T','A','T','I'}

/** Run Summary
 * - run summary
 * - origin : kAliHLTDataOriginOut ( HLT )
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTRunSummaryDataTypeID          {'R','U','N','S','U','M','M','A'}

/** Trigger decision
 * - origin : kAliHLTDataOriginOut ( HLT )
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTTriggerDecisionDataTypeID     {'T','R','I','G','_','D','E','C'}

/** Global trigger decision
 * - origin : kAliHLTDataOriginOut ( HLT )
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTGlobalTriggerDataTypeID       {'G','L','O','B','T','R','I','G'}

/** Block Statistics
 * - small block statistics info added to the data stream by
 *   the component base class
 * - origin kAliHLTDataOriginPrivate
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTComponentStatisticsDataTypeID {'C','O','M','P','S','T','A','T'}

/** Component table
 * - list of components in the chain to be percolated through the chain
 * - each component adds it's chain id string and a generated 32bit id
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTComponentTableDataTypeID      {'C','O','M','P','T','A','B','L'}

/** Forwarded component table
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTComponentFwdTableDataTypeID   {'C','O','M','P','T','A','B','F'}

/** general ROOT TObject
 * - a general TObject exported from the HLT analysis
 * - varying origin
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTTObjectDataTypeID              {'R','O','O','T','T','O','B','J'}

/** ROOT streamer info
 * - used for the transmission of streamer info for objects in the HLTOUT
 * - origin kAliHLTDataOriginOut ( HLT )
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTStreamerInfoDataTypeID         {'R','O','O','T','S','T','R','I'}

/** ROOT TObjArray
 * - a TObjArray exported from the HLT analysis
 * - varying origin
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTTObjArrayDataTypeID            {'R','O','O','T','O','B','A','R'}

/** ROOT TTree
 * - a TTree object exported from the HLT analysis
 * - varying origin
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTTTreeDataTypeID                {'R','O','O','T','T','R','E','E'}

/** ROOT histogram
 * - a histogram object exported from the HLT analysis
 * - class derives from TH1 (directly or indirectly) and inherits all common functionality
 * - varying origin
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTHistogramDataTypeID            {'R','O','O','T','H','I','S','T'}

/** ROOT TNtuple
 * - a TNtupl object exported from the HLT analysis
 * - varying origin
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTTNtupleDataTypeID              {'R','O','O','T','T','U','P','L'}

/** HLT Track
 * - Struct for Tracks based on AliExternalTrackParam
 * - varying origin
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTTrackDataTypeID                {'H','L','T','T','R','A','C','K'}

/** Track Monte Carlo information
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTTrackMCDataTypeID              {'T','R','A','C','K','_','M','C'}

/** TClonesArray of AliExternalTrackParam
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTExternalTrackParamDataTypeID   {'T','C','A','E','X','T','T','R'}

/** HLT Jet
 * - Struct for jets based on AliHLTJETJets
 * - varying origin
 * @ingroup alihlt_component_datatypes
 */
#define kAliHLTJetDataTypeID                  {'H','L','T','J','E','T','V','0'}

/** dEdx  data
 * Common data type for the dEdx 
 * format depends on the origin (detector)
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTdEdxDataTypeID {'D','E','D','X',' ',' ',' ',' '}

/** dNdPt  data
 * Common data type for the dNdPt output object
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTdNdPtDataTypeID {'D','N','D','P','T',' ',' ',' '}

/** Global input trigger counters data block type.
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTInputTriggerCountersDataTypeID      {'I','N','T','R','G','C','N','T'}

/** Global output trigger counters data block type.
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTOutputTriggerCountersDataTypeID     {'O','T','T','R','G','C','N','T'}

/** Generic meta data block type ID.
 * @ingroup alihlt_component_datatypes
 */
# define kAliHLTMetaDataTypeID                      {'M','E','T','A','D','A','T','A'}

extern "C" {
  //////////////////////////////////////////////////////////////////////////
  //
  // Basic HLT data types
  //
  //////////////////////////////////////////////////////////////////////////

  typedef unsigned char AliHLTUInt8_t;

  typedef signed char AliHLTInt8_t;

  typedef unsigned short AliHLTUInt16_t;

  typedef signed short AliHLTInt16_t;

  typedef unsigned int AliHLTUInt32_t;

  typedef signed int AliHLTInt32_t;

  typedef unsigned long long AliHLTUInt64_t;

  typedef signed long long AliHLTInt64_t;

  typedef float AliHLTFloat32_t;

  typedef double AliHLTFloat64_t;

  typedef AliHLTUInt64_t AliHLTEventID_t;

  //////////////////////////////////////////////////////////////////////////
  //
  // HLT logging levels
  //
  //////////////////////////////////////////////////////////////////////////

  /**
   * Logging severities of the HLT
   */
  enum AliHLTComponentLogSeverity {
    /** no logging */
    kHLTLogNone      = 0,
    /** benchmark messages */
    kHLTLogBenchmark = 0x1,
    /** debug messages */
    kHLTLogDebug     = 0x2,
    /** info messages */
    kHLTLogInfo      = 0x4,
    /** warning messages */
    kHLTLogWarning   = 0x8,
    /** error messages */
    kHLTLogError     = 0x10,
    /** fatal error messages */
    kHLTLogFatal     = 0x20,
    /** few important messages not to be filtered out.
     * redirected to kHLTLogInfo in AliRoot
     */
    kHLTLogImportant = 0x40,
    /** special value to enable all messages */
    kHLTLogAll       = 0x7f,
    /** the default logging filter */
    kHLTLogDefault   = 0x79
  };

  //////////////////////////////////////////////////////////////////////////
  //
  // HLT data structures for data exchange and external interface
  //
  //////////////////////////////////////////////////////////////////////////

  /**
   * @struct AliHLTComponentEventData
   * Event descriptor
   */
  struct AliHLTComponentEventData
  {
    AliHLTUInt32_t fStructSize;        /// Size of this structure in bytes.
    AliHLTEventID_t fEventID;          /// 64 bit event ID number.
    AliHLTUInt32_t fEventCreation_s;   /// Event creation time in seconds (Should be added to fEventCreation_us*1e6).
    AliHLTUInt32_t fEventCreation_us;  /// Fractional event creation time in micro seconds.
    AliHLTUInt32_t fBlockCnt;          /// The number of raw data blocks received by the component.
  };

  /**
   * @struct AliHLTComponentShmData
   * Shared memory descriptor.
   * Irrelevant for analysis components.
   */
  struct AliHLTComponentShmData
  {
    AliHLTUInt32_t fStructSize;  /// Size of this structure in bytes.
    AliHLTUInt32_t fShmType;     /// The type code of the shared memory.
    AliHLTUInt64_t fShmID;       /// The shared memory identifier.
  };

  /**
   * @defgroup alihlt_component_datatypes Common Component Data Types
   * The analysis framework defines a number of common data types for
   * usage in the detector modules, like e.g. ::kAliHLTAnyDataType
   * and ::kAliHLTDataTypeDDLRaw. Those data types always have
   * origin ::kAliHLTDataOriginAny. The correct detector origin can be
   * set by using operator '|'
   * <pre>
   * AliHLTComponentDataType dt=kAliHLTDDLRawDataTypeID|kAliHLTDataOriginTPC
   * </pre>
   * @ingroup alihlt_component
   */

  /**
   * @struct AliHLTComponentDataType
   * Data type descriptor for data blocks transferred through the processing
   * chain.
   * @ingroup alihlt_component_datatypes
   */
  struct AliHLTComponentDataType
  {
    AliHLTUInt32_t fStructSize;                            /// Size of this structure in bytes.
    char fID[kAliHLTComponentDataTypefIDsize];             /// Data type identifier.
    char fOrigin[kAliHLTComponentDataTypefOriginSize];     /// Subsystem or detector origin of the data.
    
    //assignment from a topic string
    AliHLTComponentDataType& operator=( const char topic[kAliHLTComponentDataTypeTopicSize] )
    {
      memcpy( fID, &topic[0], kAliHLTComponentDataTypefIDsize );
      memcpy( fOrigin, &topic[kAliHLTComponentDataTypefIDsize], kAliHLTComponentDataTypefOriginSize );
      return *this;
    }

    //Print this datatype to a string, bufferlen is the len of the buffer, this function will return a zero-terminated string of max len bufferLen - 1
    void PrintDataType(char* buffer, unsigned int bufferLen) const;
  };

  /**
   * @struct AliHLTComponentBlockData
   * This is the decription of data blocks exchanged between components.
   * \b IMPORTANT: The validity of fPtr and fOffset is different for input and
   * output blocks:
   * - input blocks: The \em fPtr member always points to the beginning of the data
   *                 of size \em fSize. fOffset is ignored and should be in most
   *                 case 0.
   * - output blocks: The \em fPtr member is ignored by the framework. \em fOffset
   *                  must specify the start of the data relative to the output
   *                  buffer. The data block has size \em fSize.
   */
  struct AliHLTComponentBlockData
  {
    /** size and version of the struct */
    AliHLTUInt32_t fStructSize;
    /** shared memory key, ignored by processing components */
    AliHLTComponentShmData fShmKey;
    /** offset of output data relative to the output buffer */
    AliHLTUInt32_t fOffset;
    /** start of the data for input data blocks, fOffset to be ignored*/
    void* fPtr;
    /** size of the data block */
    AliHLTUInt32_t fSize;
    /** data type of the data block */
    AliHLTComponentDataType fDataType;
    /** data specification of the data block */
    AliHLTUInt32_t fSpecification;

    AliHLTComponentDataType GetDataType() const {return fDataType;}
    AliHLTUInt32_t GetSpecification() const {return fSpecification;}
  };

  /**
   * Helper function to compare topics
   * a topic is a string representation of AliHLTComponentDataType
   */
  inline bool Topicncmp(const char* topic, const char* reference, int topicSize=kAliHLTComponentDataTypeTopicSize, int referenceSize=kAliHLTComponentDataTypeTopicSize)
  {
    for (int i=0; i<((topicSize<referenceSize)?topicSize:referenceSize); i++)
    {
      if (!(topic[i]=='*' || reference[i]=='*' || 
            topic[i]=='\0' || reference[i]=='\0' || 
            topic[i]==reference[i])) {
        return false;
      }
    }
    return true;
  }

  //this struct is meant to be used as a universal data block descriptor ("topic" + specification)
  //for ZMQ communication
  struct AliHLTDataTopic
  {
    char fTopic[kAliHLTComponentDataTypeTopicSize]; /// Data type identifier + source id as char array.
    AliHLTUInt32_t fSpecification;                  /// data specification of the data block
   
    //ctor
    AliHLTDataTopic()
      : fTopic()
      , fSpecification(0)
    {
    }

    //copy ctor
    AliHLTDataTopic(const AliHLTComponentDataType& dataType)
      : fTopic()
      , fSpecification(0)
    {
      memcpy( fTopic, dataType.fID, kAliHLTComponentDataTypefIDsize );
      memcpy( fTopic+kAliHLTComponentDataTypefIDsize, dataType.fOrigin, kAliHLTComponentDataTypefOriginSize );
    }

    //copy ctor
    AliHLTDataTopic(const AliHLTComponentBlockData& blockData)
      : fTopic()
      , fSpecification(blockData.fSpecification)
    {
      memcpy( fTopic, blockData.fDataType.fID, kAliHLTComponentDataTypefIDsize );
      memcpy( fTopic+kAliHLTComponentDataTypefIDsize, blockData.fDataType.fOrigin, kAliHLTComponentDataTypefOriginSize );
    }

    //partial (no fSpecification) copy from AliHLTComponentDataType
    AliHLTDataTopic& operator=( const AliHLTComponentDataType& dataType )
    {
      memcpy( fTopic, dataType.fID, kAliHLTComponentDataTypefIDsize );
      memcpy( fTopic+kAliHLTComponentDataTypefIDsize, dataType.fOrigin, kAliHLTComponentDataTypefOriginSize );
      return *this;
    }

    //assignment from a AliHLTComponentBlockData
    AliHLTDataTopic& operator=( const AliHLTComponentBlockData& blockData )
    {
      memcpy( fTopic, blockData.fDataType.fID, kAliHLTComponentDataTypefIDsize );
      memcpy( fTopic+kAliHLTComponentDataTypefIDsize, blockData.fDataType.fOrigin, kAliHLTComponentDataTypefOriginSize );
      fSpecification = blockData.fSpecification;
      return *this;
    }

    bool operator==( const AliHLTDataTopic& dt )
    {
      bool topicMatch = Topicncmp(dt.fTopic, fTopic);
      return topicMatch;
    }

    std::string Description() const
    {
      std::string description(fTopic, kAliHLTComponentDataTypeTopicSize);
      description+=" spec:";
      char numstr[21];
      snprintf(numstr, 21, "%x", fSpecification);
      description+=numstr;
      return description;
    }

    std::string GetOrigin() const
    {
      std::string origin(fTopic+kAliHLTComponentDataTypefIDsize, kAliHLTComponentDataTypefOriginSize);
      return origin;
    }

    std::string GetID() const
    {
      std::string id(fTopic, kAliHLTComponentDataTypefIDsize);
      return id;
    }

  };

  /**
   * @struct AliHLTComponentEventDoneData
   * 
   */
  struct AliHLTComponentEventDoneData
  {
    AliHLTUInt32_t fStructSize;   /// Size of this structure in bytes.
    AliHLTUInt32_t fDataSize;     /// Size of the data section (following this data member) in bytes.
    void* fData;                  /// Start of the data section.
  };

  /**
   * @struct AliHLTRunDesc
   * Event descriptor.
   * The struct is sent with the SOR and EOR events.
   *
   * @note
   * The name of the member fRunType is a bit misleading. This is not
   * the ALICE Run Type given by the ECS to the sub-system. The member
   * is an internal HLT run type and a combination of the HLT running
   * mode and the beam type.
   * <pre>
   * Bit 0-2:   beam type identifier
   * Bit 3-31:  HLT mode
   * </pre>
   */
  struct AliHLTRunDesc
  {
    AliHLTUInt32_t fStructSize;   /// Size of this structure in bytes.
    AliHLTUInt32_t fRunNo;        /// The run number for the current active run.
    AliHLTUInt32_t fRunType;      /// The HLT run type.
  };

  /**
   * @struct AliHLTComponentStatistics
   * Small block size summary added by the AliHLTComponent base class
   * if component statistics are enabled (--enable-compstat).
   *
   * fLevel is retrieved from incoming block statistics and incremented. 
   * Incoming block statistics are appended to the newly added one if
   * --enable-compstat=full has been chosen.
   *
   * ChangeLog:
   *   2009-01-14 fComponentCycleTime added
   */
  struct AliHLTComponentStatistics
  {
    AliHLTUInt32_t fStructSize;           /// Size of this structure in bytes.
    AliHLTUInt32_t fLevel;                /// Indicates from which processing stage this information is from.
    AliHLTUInt32_t fId;                   /// Unique identifier for the chain based on CRC code.
    AliHLTUInt32_t fTime;                 /// Real wall time used to process the data (micro seconds).
    AliHLTUInt32_t fCTime;                /// CPU time used to process the data (micro seconds).
    AliHLTUInt32_t fInputBlockCount;      /// Number of input data blocks.
    AliHLTUInt32_t fTotalInputSize;       /// Total size in bytes of input data.
    AliHLTUInt32_t fOutputBlockCount;     /// Number of output data blocks.
    AliHLTUInt32_t fTotalOutputSize;      /// Total size in bytes of output data.
    AliHLTUInt32_t fComponentCycleTime;   /// Real wall time indicating the start of the data processing (micro seconds).
  };

  /**
   * @struct AliHLTComponentTableEntry
   * Structure to be send on SOR event through the chain.
   * The 'length' of the structure is variable and depends on the length
   * of the buffer at the end.
   *
   * ComponentTableEntries are sent with data type @ref kAliHLTDataTypeComponentTable
   * and are identified by a 32bit Id specification generated by a CRC
   * algorithm from the chain Id of the component. This is not a 100% unique
   * id but with a high probability. This approach accounts for the fact
   * that all components are separated processes. 
   *
   * The buffer consists of an array of 32bit Ids containing the Ids of
   * all direct parents taken from the specification of the data blocks.
   * The number of parents is stored in fNofParents. Each component forwards the
   * incoming component table entries with data type @ref kAliHLTDataTypeComponentFwdTable
   * by that the direct parents can be identified.
   *
   * Following this array a description string contains the chain id, component args, and
   * maybe more properties in the future. The current format is
   * 'chain_id{component_id:component args}' e.g. TPC-CF_00_0{TPCClusterFinder32Bit:-deconvolute-time}
   */
  struct AliHLTComponentTableEntry
  {
    AliHLTUInt32_t fStructSize;           /// Size of this structure in bytes.
    AliHLTUInt32_t fLevel;                /// Indicates from which processing stage this information is from.
    AliHLTUInt16_t fNofParents;           /// size of the array of parent ids
    AliHLTUInt8_t  fSizeDescription;      /// size of the description string in the appended buffer
    AliHLTUInt8_t  fBuffer[1];            /// the strings: chain id, component args, reserved
  };

  //////////////////////////////////////////////////////////////////////////
  //
  // Trigger meta information
  //
  //////////////////////////////////////////////////////////////////////////

  /** field size of fAttribute */
  const int gkAliHLTBlockDAttributeCount = 8;

  /** field size of fCommonHeader */
  const int gkAliHLTCommonHeaderCountV2 = 8;
  const int gkAliHLTCommonHeaderCountV3 = 10;
  const int gkAliHLTCommonHeaderCount = gkAliHLTCommonHeaderCountV3;

  /** size of the DDL list first version */
  const int gkAliHLTDDLListSizeV0 = 30;

  /** size of the DDL list after DCAL added to EMCAL */
  const int gkAliHLTDDLListSizeV1 = 31;

  /** size of the DDL list with AD */
  const int gkAliHLTDDLListSizeV2 =32;

  /** size of the DDL list */
  const int gkAliHLTDDLListSize = gkAliHLTDDLListSizeV2;

  /** Number of Trigger Classes of CTP in CDH */
  const int gkNCTPTriggerClassesV2 = 50;
  const int gkNCTPTriggerClassesV3 = 100;
  const int gkNCTPTriggerClasses = gkNCTPTriggerClassesV3;

  // make it also available as define for templates
#define NCTPTRIGGERCLASSES 100

  /**
   * @struct AliHLTEventDDLV0
   * First version of the DDL list event.
   * The struct is send with the DDLLIST event.
   * Used in the trigger structure for internal apperance of 
   * the DLLs as well as for the HLT readout list send to DAQ 
   * ( as DataType : kAliHLTDataTypeDDL )
   */
  struct AliHLTEventDDLV0
  {
    AliHLTUInt32_t fCount;                       /// Indicates the number of words in fList.
    AliHLTUInt32_t fList[gkAliHLTDDLListSizeV0];   /// The list of DDL enable/disable bits.
  };

  /**
   * @struct AliHLTEventDDLV1
   * DDL list event structure with extra word for DCAL bits.
   */
  struct AliHLTEventDDLV1
  {
    AliHLTUInt32_t fCount;                       /// Indicates the number of words in fList.
    AliHLTUInt32_t fList[gkAliHLTDDLListSizeV1];   /// The list of DDL enable/disable bits.
  };
  
  /**
   * @struct AliHLTEventDDLV2
   * DDL list event structure with extra word for AD bits.
   */
  struct AliHLTEventDDLV2
  {
    AliHLTUInt32_t fCount;                       /// Indicates the number of words in fList.
    AliHLTUInt32_t fList[gkAliHLTDDLListSizeV2];   /// The list of DDL enable/disable bits.
  };
  
  /**
   * @typedef AliHLTEventDDL
   * Current used default version of the AliHLTEventDDL structure.
   */
  typedef AliHLTEventDDLV2 AliHLTEventDDL;

  /**
   * @struct AliHLTEventTriggerData
   */
  struct AliHLTEventTriggerData
  {
    AliHLTUInt8_t  fAttributes[gkAliHLTBlockDAttributeCount];  /// List of data block attibutes.
    AliHLTUInt64_t fHLTStatus; /// Bit field 
    AliHLTUInt32_t fCommonHeaderWordCnt;  /// Number of words in fCommonHeader.
    AliHLTUInt32_t fCommonHeader[gkAliHLTCommonHeaderCount];  /// The common header words.
    union
    {
      AliHLTEventDDL fReadoutList;   /// The default readout list structure.
      AliHLTEventDDLV0 fReadoutListV0;   /// Access to the old version of the readout list structure.
      AliHLTEventDDLV1 fReadoutListV1;   /// Access to the readout list structure with DCAL included.
      AliHLTEventDDLV2 fReadoutListV2;   /// Access to the readout list structure with AD included.
    };
  };

  /**
   * @struct AliHLTComponentTriggerData
   * Trigger data
   */
  struct AliHLTComponentTriggerData
  {
    AliHLTUInt32_t fStructSize;  /// Size of this structure in bytes.
    AliHLTUInt32_t fDataSize;    /// Size of the data section (following this data member) in bytes.
    void* fData;                 /// Start of the data section.
  };

  //////////////////////////////////////////////////////////////////////////
  //
  // HLT Event Type Specification
  //
  //////////////////////////////////////////////////////////////////////////

  /** Unknown eventType specification */
  const AliHLTUInt32_t gkAliEventTypeUnknown = ~(AliHLTUInt32_t)0;
  /** SOR eventType specification */ 
  const AliHLTUInt32_t gkAliEventTypeStartOfRun=1;
  /** Data eventType specification */
  const AliHLTUInt32_t gkAliEventTypeData=2;
  /** EOR eventType specification */ 
  const AliHLTUInt32_t gkAliEventTypeEndOfRun=4;
  /** Corrupt eventType specification */
  const AliHLTUInt32_t gkAliEventTypeCorruptID=8;
  /** Calibration eventType specification */ 
  const AliHLTUInt32_t gkAliEventTypeCalibration=16;
  /** Software eventType specification */ 
  const AliHLTUInt32_t gkAliEventTypeSoftware=24;
  /** DataReplay eventType specification */
  const AliHLTUInt32_t gkAliEventTypeDataReplay=32;
  /** Configuration eventType specification */
  const AliHLTUInt32_t gkAliEventTypeConfiguration=34;
  /** Update DCS eventType specification */
  const AliHLTUInt32_t gkAliEventTypeReadPreprocessor=35;
  /** Tick eventType specification */ 
  const AliHLTUInt32_t gkAliEventTypeTick=64;
  /** Max eventType specification */ 
  const AliHLTUInt32_t gkAliEventTypeMax=64;

  //////////////////////////////////////////////////////////////////////////
  //
  // HLT defines and defaults
  //
  //////////////////////////////////////////////////////////////////////////

  /** invalid event id 
   * @ingroup alihlt_component_datatypes
   */
  const AliHLTEventID_t kAliHLTVoidEventID=~(AliHLTEventID_t)0;

  /** invalid data specification 
   * @ingroup alihlt_component_datatypes
   */
  const AliHLTUInt32_t kAliHLTVoidDataSpec = ~(AliHLTUInt32_t)0;

  /** invalid run no
   * @ingroup alihlt_component_datatypes
   */
  const AliHLTUInt32_t kAliHLTVoidRunNo = ~(AliHLTUInt32_t)0;

  /** invalid run type
   * @ingroup alihlt_component_datatypes
   */
  const AliHLTUInt32_t kAliHLTVoidRunType = ~(AliHLTUInt32_t)0;

  /** invalid run descriptor
   * @ingroup alihlt_component_datatypes
   */
  const AliHLTRunDesc kAliHLTVoidRunDesc={sizeof(AliHLTRunDesc), kAliHLTVoidRunNo, kAliHLTVoidRunType};

  /** invalid shared memory type */
  const AliHLTUInt32_t gkAliHLTComponentInvalidShmType = 0;

  /** invalid shared memory id */
  const AliHLTUInt64_t gkAliHLTComponentInvalidShmID = ~(AliHLTUInt64_t)0;

  /** invalid data type 
   * @ingroup alihlt_component_datatypes
   */
  const AliHLTComponentDataType kAliHLTVoidDataType = {
    sizeof(AliHLTComponentDataType),
    kAliHLTVoidDataTypeID,
    kAliHLTDataOriginVoid
  };

  /** all data types, means any + void data type
   * @ingroup alihlt_component_datatypes
   */
  const AliHLTComponentDataType kAliHLTAllDataTypes = {
    sizeof(AliHLTComponentDataType),
    kAliHLTAllDataTypesID,
    kAliHLTDataOriginAny
  };

  // there is currently a problem with rootcint if the predefined ids
  // (commented below) are used. rootcint does not find the id if they
  // are char arrays defined with {} and individual chars. If strings
  // are used it works fine
  /** any data type 
   * @ingroup alihlt_component_datatypes
   */
  const AliHLTComponentDataType kAliHLTAnyDataType = {
    sizeof(AliHLTComponentDataType),
    kAliHLTAnyDataTypeID,
    kAliHLTDataOriginAny
  };

  /** multiple output data types 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTMultipleDataType;

  /** data to file exchange subscriber 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeFXSCalib;

  /** DDL list data type 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeDDL;

  /** DAQ readout list 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeDAQRDOUT;

  /** CLUSTERS data
   * Common data type for the output of cluster finders, the exact
   * format depends on the origin (detector)
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeClusters;

  /** SOR data type 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeSOR;

  /** EOR data type 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeEOR;

  /** Run type data block 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeRunType;

  /** Event type specification 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeEvent;

  /** ECS parameter event 
   * - sent during the SOR event by the framework
   * - contains the full ECS parameter string
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeECSParam; // {ECSPARAM:PRIV}

  /** Configuration event data type 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeComConf;

  /** Direct configuration string block data type
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeConfig;

  /** Info string block data type
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeInfo;

  /** CDB entry block data type
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeCDBEntry;

  /** DCS value update event 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeUpdtDCS;

  /** RAW DDL data specification, origin is 'any', data publisher origin correctly 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeDDLRaw;

  /** AliMCEvent object data specification, origin is 'OFFL' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeMCObject;

  /** ESD vertex object data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeESDVertex;

   /** KF vertex object data specification, origin is 'any'
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeKFVertex;

  /** global vertexer data specification, origin is 'any'
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeGlobalVertexer;

  /** primary finder data specification, origin is 'any'
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypePrimaryFinder;

  /** primary finder data specification, origin is 'any'
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeV0Finder;

  /** flat ESD object data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeFlatESD;

 /** flat ESD friend object data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeFlatESDFriend;

  /** flat ESD vertex object data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeFlatESDVertex;

  /** ESD object data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeESDObject;

  /** ESD friend object data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeESDfriendObject;

  /** ESD content data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeESDContent;

  /** ESD friend content data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeESDFriendContent;

  /** ESD Tree data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeESDTree;

  /** AliRoot TreeD data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeAliTreeD;

  /** AliRoot TreeR data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeAliTreeR;

  /** 16 bit Hardware address selection data specification, origin is 'any' 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeHwAddr16;

  /** Event statistics 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeEventStatistics;

  /** Event summary 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeEventSummary;

  /** Event statistics 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeRunStatistics;

  /** Run summary 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeRunSummary;

  /** Trigger decision
   * - origin : kAliHLTDataOriginOut ( HLT )
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeTriggerDecision;   // {TRIG_DEC:HLT }

  /** Trigger decision
   * - origin : kAliHLTDataOriginOut ( HLT )
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeReadoutList;   // {HLTRDLST:HLT }

  /** Global trigger decision
   * - origin : kAliHLTDataOriginOut ( HLT )
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeGlobalTrigger;     // {GLOBTRIG:HLT }

  /** Component block statistics
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeComponentStatistics;

  /** Component table
   * To be sent on SOR event, each component adds it's chain id string
   * and a generated 32bit identifier to the table
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeComponentTable;

  /** Forwarded component table
   * To be sent on SOR event, each component forwards blocks of type
   * @ref kAliHLTDataTypeComponentTable was kAliHLTDataTypeComponentFwdTable
   * after adding the parent ids to its own table struct.
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeComponentFwdTable;

  /**
   * Data type for the Common Data Header and readout list information sent by TCPDumpSubscriber.
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeTriggerMetaBlock;     // {METADATA:PRIV}

  //////////////////////////////////////////////////////////////////////////
  //
  // Data Types for Monitoring objects
  //
  //////////////////////////////////////////////////////////////////////////

  /** general ROOT TObject 
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeTObject;            // {ROOTTOBJ,"***"}

  /** ROOT streamer info
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeStreamerInfo;       // {ROOTSTRI,HLT }
									  		
  /** ROOT TObjArray 
   * @ingroup alihlt_component_datatypes
   */							  		
  extern const AliHLTComponentDataType kAliHLTDataTypeTObjArray;	  // {ROOTOBAR,"***"}
									  		
  /** ROOT TTree 
   * @ingroup alihlt_component_datatypes
   */							  		
  extern const AliHLTComponentDataType kAliHLTDataTypeTTree;		  // {ROOTTREE,"***"}
									  		
  /** ROOT TH1 (can be used for all histograms, they derive from TH1) 
   * @ingroup alihlt_component_datatypes
   */  		
  extern const AliHLTComponentDataType kAliHLTDataTypeHistogram;	  // {ROOTHIST,"***"}
									  		
  /** ROOT TNtuple 
   * @ingroup alihlt_component_datatypes
   */							  		
  extern const AliHLTComponentDataType kAliHLTDataTypeTNtuple;		  // {ROOTTUPL,"***"}

  /** Global input trigger counters.
   * - origin : kAliHLTDataOriginOut ( HLT )
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeInputTriggerCounters;     // {INTRGCNT:HLT }

  /** Global output trigger counters.
   * - origin : kAliHLTDataOriginOut ( HLT )
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeOutputTriggerCounters;     // {OTTRGCNT:HLT }

  /** General track array for the barrel tracks based on AliExternalTrackParam
   * Data format defined by AliHLTTracksData
   *
   * We follow the naming scheme of AliESDEvent where 'Tracks' denote the
   * barrel tracks and detector tracks get names 'DETTracks'
   * @ingroup alihlt_component_datatypes
   */	
  extern const AliHLTComponentDataType kAliHLTDataTypeTrack;              // {HLTTRACK,"***"}

  /** Track Monte Carlo information
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeTrackMC;            // {TRACK_MC,"***"}

  /** TClonesArray of AliExternalTrackParam
   * @ingroup alihlt_component_datatypes
   */	
  extern const AliHLTComponentDataType kAliHLTDataTypeExternalTrackParam; // {TCAEXTTR,"***"}

  /** Container containing jets (AliHLTJETJets)
   * Containing TClonesArray of AliAODJets 
   * @ingroup alihlt_component_datatypes
   */	
  extern const AliHLTComponentDataType kAliHLTDataTypeJet;                // {HLTJETV0,"***"}
  
  /** Container of ITS tracks
   * @ingroup alihlt_component_datatypes
   */	
  extern const AliHLTComponentDataType fgkITSTracksDataType;

  /** Container of ITS SAP tracker data
   * @ingroup alihlt_component_datatypes
   */	
  extern const AliHLTComponentDataType kAliHLTDataTypeITSSAPData;

  /** Container of calorimeter clusters
   * @ingroup alihlt_component_datatypes
   */	
  extern const AliHLTComponentDataType kAliHLTDataTypeCaloCluster; 

  /** Container of calorimeter triggers
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypeCaloTrigger;

  /** Container of dEdx
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypedEdx;

  /** Container of dNdPt
   * @ingroup alihlt_component_datatypes
   */
  extern const AliHLTComponentDataType kAliHLTDataTypedNdPt;
  
  extern const AliHLTComponentDataType kAliHLTDataTypeCustomTrigger;

  //////////////////////////////////////////////////////////////////////////
  //
  // FXS subscriber meta information
  //
  //////////////////////////////////////////////////////////////////////////

  const int gkAliHLTFXSHeaderfOriginSize = 4;
  const int gkAliHLTFXSHeaderfFileIDSize = 128;
  const int gkAliHLTFXSHeaderfDDLNumberSize = 64;

  /** Header in front of the data payload, in order to sent data to the FXS. */
  struct AliHLTFXSHeader
  {
    AliHLTUInt32_t fHeaderVersion;   /// HLT software version number.
    AliHLTUInt32_t fRunNumber;       /// The current run number.
    char fOrigin[gkAliHLTFXSHeaderfOriginSize];   /// The detector from which the FXS data is received.
    char fFileID[gkAliHLTFXSHeaderfFileIDSize];   /// File identifier for the stored data.
    char fDDLNumber[gkAliHLTFXSHeaderfDDLNumberSize];  /// The DDL bits.
  };  

  //////////////////////////////////////////////////////////////////////////
  //
  // Component running environment
  //
  //////////////////////////////////////////////////////////////////////////

  /** definition of a void fct pointer */
  typedef void (*AliHLTfctVoid)();

  /** logging function */
  typedef int (*AliHLTfctLogging)( void* param, 
				   AliHLTComponentLogSeverity severity,
				   const char* origin,
				   const char* keyword,
				   const char* message);

  /**
   * @struct AliHLTAnalysisEnvironment
   * Running environment for analysis components.
   * The struct describes function callbacks for actions to be
   * carried out by the calling framework, like memory allocation,
   * property callbecks, logging, etc.
   *
   * @ingroup alihlt_wrapper_interface
   */
  struct AliHLTAnalysisEnvironment
  {
    /** size of the structure */
    AliHLTUInt32_t fStructSize;

    /** the component parameter given by the framework on creation */
    void* fParam;

    /** allocated memory */
    void* (*fAllocMemoryFunc)( void* param, unsigned long size );

    /** allocate an EventDoneData structure. */
    int (*fGetEventDoneDataFunc)( void* param, AliHLTEventID_t eventID, unsigned long size, AliHLTComponentEventDoneData** edd );

    /** logging callback */
    AliHLTfctLogging fLoggingFunc;
  };
#if 0
  // I just keep this as a note pad. Has to be added to the end of the structure
  // future addition already foreseen/envisioned
  // IMPORTANT: don not just remove the defines as this breaks the binary
  // compatibility
  int (*fAllocShmMemoryFunc)( void* param, unsigned long size, AliHLTComponentBlockData* blockLocation );
#endif

  /**
   * @struct AliHLTComponentEnvironment
   * This was the original definition of the running environment.
   * Due to a bug in the AliRootWrapperSubscriber/SimpleComponentWrapper,
   * this structure can not be used any longer but is kept for backward
   * compatibility. 
   * @note The external interface provided by the libHLTbase is now kept
   * frozen but should not be used any more. Use the interface provided
   * by the libHLTinterface library.
   *
   * @ingroup alihlt_wrapper_interface_deprecated
   */
  struct AliHLTComponentEnvironment
  {
    AliHLTUInt32_t fStructSize;
    void* fParam;
    void* (*fAllocMemoryFunc)( void* param, unsigned long size );
    int (*fGetEventDoneDataFunc)( void* param, AliHLTEventID_t eventID, unsigned long size, AliHLTComponentEventDoneData** edd );
    AliHLTfctLogging fLoggingFunc;
  };

  //////////////////////////////////////////////////////////////////////////
  //
  // The external interface definition
  //
  //////////////////////////////////////////////////////////////////////////

  /**
   * The component handle.
   * Used as indification in the outside world.
   * @ingroup alihlt_wrapper_interface
   */
  typedef void* AliHLTComponentHandle;

  /** @ingroup alihlt_wrapper_interface */
  const AliHLTComponentHandle kEmptyHLTComponentHandle = 0;

  /**
   * Get a system call of the interface.
   * @param function signature
   * @return pointer to system call
   * @ingroup alihlt_wrapper_interface
   */
  typedef void* (*AliHLTAnalysisFctGetInterfaceCall)(const char*);

# define ALIHLTANALYSIS_INTERFACE_LIBRARY  "libHLTinterface.so"
# define ALIHLTANALYSIS_FCT_GETINTERFACECALL  "AliHLTAnalysisGetInterfaceCall"

  /** @ingroup alihlt_wrapper_interface */
  typedef int (*AliHLTExtFctInitSystem)( unsigned long version, AliHLTAnalysisEnvironment* externalEnv, unsigned long runNo, const char* runType );

  /** @ingroup alihlt_wrapper_interface */
  typedef int (*AliHLTExtFctDeinitSystem)();

  /** @ingroup alihlt_wrapper_interface */
  typedef int (*AliHLTExtFctLoadLibrary)( const char* );

  /** @ingroup alihlt_wrapper_interface */
  typedef int (*AliHLTExtFctUnloadLibrary)( const char* );

  /** @ingroup alihlt_wrapper_interface */
  typedef int (*AliHLTExtFctCreateComponent)( const char*, void*, int, const char**, AliHLTComponentHandle*, const char* description );

  /** @ingroup alihlt_wrapper_interface */
  typedef int (*AliHLTExtFctDestroyComponent)( AliHLTComponentHandle );

  /** @ingroup alihlt_wrapper_interface */
  typedef int (*AliHLTExtFctProcessEvent)( AliHLTComponentHandle, const AliHLTComponentEventData*, const AliHLTComponentBlockData*, 
					   AliHLTComponentTriggerData*, AliHLTUInt8_t*,
					   AliHLTUInt32_t*, AliHLTUInt32_t*, 
					   AliHLTComponentBlockData**,
					   AliHLTComponentEventDoneData** );

  /** @ingroup alihlt_wrapper_interface */
  typedef int (*AliHLTExtFctGetOutputDataType)( AliHLTComponentHandle, AliHLTComponentDataType* );

  /** @ingroup alihlt_wrapper_interface */
  typedef int (*AliHLTExtFctGetOutputSize)( AliHLTComponentHandle, unsigned long*, double* );

}

#include <bitset>  
typedef std::bitset<NCTPTRIGGERCLASSES> AliHLTTriggerMask_t;

using namespace std;

//////////////////////////////////////////////////////////////////////////
//
// Data type helper functions
//
//////////////////////////////////////////////////////////////////////////

/** exact comparison of HLT component data types
 * @ingroup alihlt_component_datatypes
 */
inline bool MatchExactly( const AliHLTComponentDataType& dt1, const AliHLTComponentDataType& dt2 )
{
  for ( int i = 0; i < kAliHLTComponentDataTypefIDsize; i++ )
    if ( dt1.fID[i] != dt2.fID[i] )
      return false;
  for ( int i = 0; i < kAliHLTComponentDataTypefOriginSize; i++ )
    if ( dt1.fOrigin[i] != dt2.fOrigin[i] )
      return false;
  return true;
}

/** Comparison operator for HLT component data types.
 * The operator takes wildcards into account, i.e. the ::kAliHLTAnyDataType,
 * ::kAliHLTAnyDataTypeID and ::kAliHLTDataOriginAny definitions.
 * @ingroup alihlt_component_datatypes
 */
inline bool operator==( const AliHLTComponentDataType& dt1, const AliHLTComponentDataType& dt2 )
{
  if (MatchExactly(dt1, kAliHLTAllDataTypes)) return true;
  if (MatchExactly(dt2, kAliHLTAllDataTypes)) return true;

  bool any1=true, any2=true, void1=true, void2=true, match=true;
  for ( int i = 0; i < kAliHLTComponentDataTypefOriginSize; i++ ) {
    any1&=(dt1.fOrigin[i]==kAliHLTDataOriginAny[i]);
    any2&=(dt2.fOrigin[i]==kAliHLTDataOriginAny[i]);
    void1&=(dt1.fOrigin[i]==kAliHLTDataOriginVoid[i]);
    void2&=(dt2.fOrigin[i]==kAliHLTDataOriginVoid[i]);
    match&=dt1.fOrigin[i]==dt2.fOrigin[i];
    if (!(match || (any2 && !void1) || (any1 && !void2)))
      return false;
  }

  any1=true, any2=true, match=true;
  for ( int i = 0; i < kAliHLTComponentDataTypefIDsize; i++ ) {
    any1&=(dt1.fID[i]==kAliHLTAnyDataTypeID[i]);
    any2&=(dt2.fID[i]==kAliHLTAnyDataTypeID[i]);
    void1&=(dt1.fID[i]==kAliHLTVoidDataTypeID[i]);
    void2&=(dt2.fID[i]==kAliHLTVoidDataTypeID[i]);
    match&=dt1.fID[i]==dt2.fID[i];
    if (!(match || (any2 && !void1) || (any1 && !void2)))
      return false;
  }
  return true;
}

/** Comparison operator for HLT component data types
 * Invers of operator==
 * @ingroup alihlt_component_datatypes
 */
inline bool operator!=( const AliHLTComponentDataType& dt1, const AliHLTComponentDataType& dt2 )
{
  return !(dt1==dt2);
}

/** merge operator for HLT component data types and origins
 * @ingroup alihlt_component_datatypes
 */
inline AliHLTComponentDataType operator|(const AliHLTComponentDataType srcdt, const char origin[kAliHLTComponentDataTypefOriginSize])
{
  AliHLTComponentDataType dt=srcdt;
  for ( int i = 0; i < kAliHLTComponentDataTypefOriginSize; i++ )
    dt.fOrigin[i]=origin[i];
  return dt;
}

/**
 * Helper function to initialize a data type from an id char array and origin string.
 * @return data type structure initialized with the specified id and origin
 * @ingroup alihlt_component_datatypes
 */
inline AliHLTComponentDataType AliHLTComponentDataTypeInitializer(const char id[kAliHLTComponentDataTypefIDsize], const char* origin)
{
  AliHLTComponentDataType dt=kAliHLTVoidDataType;
  int i=0;
  for (i = 0; i < kAliHLTComponentDataTypefIDsize && id[i]!=0; i++)
    dt.fID[i]=id[i];
  for (i = 0; i < kAliHLTComponentDataTypefOriginSize && origin[i]!=0; i++ )
    dt.fOrigin[i]=origin[i];
  return dt;
}


/**
 * Helper function as above, but takes 0 terminates string input and pads with  spaces on the right
 */
 
inline AliHLTComponentDataType AliHLTComponentDataTypeInitializerWithPadding(const char* ID, const char* origin)
{
  char src[kAliHLTComponentDataTypefIDsize + 1];
  char org[kAliHLTComponentDataTypefOriginSize + 1];
  int j;
  int max = kAliHLTComponentDataTypefIDsize < strlen(ID) ? kAliHLTComponentDataTypefIDsize : strlen(ID);
  for (j = 0;j < max;j++) src[j] = ID[j];
  for (;j < kAliHLTComponentDataTypefIDsize;j++) src[j] = ' ';
  src[j] = 0;
  max = kAliHLTComponentDataTypefOriginSize < strlen(origin) ? kAliHLTComponentDataTypefOriginSize : strlen(origin);
  for (j = 0;j < max;j++) org[j] = origin[j];
  for (;j < kAliHLTComponentDataTypefOriginSize;j++) org[j] = ' ';
  org[j] = 0;
  return AliHLTComponentDataTypeInitializer(src, org);
}

/**
 * Helper function to initialize a data type from a default data type and
 * an origin string. Basically it merges the specified origin into the data
 * type.
 * @return data type structure initialized with the id from specified data type
 *         and origin
 * @ingroup alihlt_component_datatypes
 */
inline AliHLTComponentDataType AliHLTComponentDataTypeInitializer(const AliHLTComponentDataType src, const char* origin)
{
  return AliHLTComponentDataTypeInitializer(src.fID, origin);
}

#endif 
