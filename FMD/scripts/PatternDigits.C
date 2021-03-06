//____________________________________________________________________
//
// $Id$
//
// Draw hits in the specialised FMD event display 
//
/** Display hits 
    @ingroup FMD_script
 */
void
PatternDigits()
{
  AliLog::SetModuleDebugLevel("FMD", 1);
  AliCDBManager* cdb = AliCDBManager::Instance();
  cdb->SetDefaultStorage("local://$ALICE_ROOT/OCDB");
  cdb->SetRun(0);
  AliFMDParameters::Instance()->Init();
  gSystem->Load("libFMDutil");
  AliFMDPattern* d = new AliFMDPattern;
  d->AddLoad(AliFMDInput::kDigits);
  d->SetName("digit");
  d->SetTitle("Digits");
  // d->AddLoad(AliFMDInput::kKinematics);
  d->Run();
}

//____________________________________________________________________
//
// EOF
//
