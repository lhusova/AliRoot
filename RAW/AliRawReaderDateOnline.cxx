/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

///////////////////////////////////////////////////////////////////////////////
///
/// This is a class for reading raw data from a date monitoring libraries.
/// It supports two modes - event taken from shared memory via DATE monitoring
/// libs, or an emulation mode when the events are taken from a DATE file using
/// the same monitoring libs.
/// The constructor requires an argument:
///
/// : - events are taken from shared memory
///  or
/// <DATE_filename> - events are taken from date file
///
/// Cvetan Cheshkov 1/04/2008
///////////////////////////////////////////////////////////////////////////////

#include "AliRawReaderDateOnline.h"

ClassImp(AliRawReaderDateOnline)

AliRawReaderDate::AliRawReaderDate(
#ifdef ALI_DATE
				   const char* filename
#else
				   const char* /* filename */
#endif
				   ) :
  AliRawReaderDate()
{

// Constructor
// Initialize the DATE monitoring libs

#ifdef ALI_DATE

  int status;

  /* define data source : this is argument 1 */  
  status=monitorSetDataSource( filename );
  if (status!=0) {
    AliFatal(Form("monitorSetDataSource() failed : %s",monitorDecodeError(status)));
  }

  /* declare monitoring program */
  status=monitorDeclareMp( __FILE__ );
  if (status!=0) {
    AliFatal(Form("monitorDeclareMp() failed : %s",monitorDecodeError(status)));
  }

  /* define wait event timeout - 1s max */
  monitorSetNowait();
  monitorSetNoWaitNetworkTimeout(1000);
  
#else
  Fatal("AliRawReaderDateOnline", "this class was compiled without DATE");
#endif
}

Bool_t AliRawReaderDate::NextEvent()
{
// wait and get the next event
// from shared memory

#ifdef ALI_DATE

  if (fEvent) free(fEvent);

  while (1) {
    /* get next event (blocking call until timeout) */
    int status=monitorGetEventDynamic(&fEvent);
    struct eventHeaderStruct *event=(eventHeaderStruct*)eventPtr;

    if (status==MON_ERR_EOF) {
      AliInfo("End of File detected");
      return kFALSE; /* end of monitoring file has been reached */
    }
    
    if (status!=0) {
      AliError(Form("monitorGetEventDynamic() failed : %s\n",monitorDecodeError(status)));
      return kFALSE;
    }
    
    /* retry if got no event */
    if (event==NULL) {
      continue;
    }

    eventTypeType eventT=event->eventType;
    /* exit when last event received, no need to wait for TERM signal */
    if (eventT==END_OF_RUN) {
      AliInfo("EOR event detected");
      return kFALSE;
    }
    if (eventT!=PHYSICS_EVENT) {
      continue;
    }

    AliInfo(Form("Run #%lu, event size: %lu, BC:%u, Orbit:%u, Period:%u",
		 (unsigned long)event->eventRunNb,
		 (unsigned long)event->eventSize,
		 EVENT_ID_GET_BUNCH_CROSSING(event->eventId),
		 EVENT_ID_GET_ORBIT(event->eventId),
		 EVENT_ID_GET_PERIOD(event->eventId)
		 ));
  }

  return AliRawRederDate::NextEvent();
}

#endif

  return kFALSE;
}


