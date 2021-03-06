from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'PbPb_5TeV_HardProbes_Dfinder_skimmed_1unit_part1_26March'
config.General.workArea = config.General.requestName

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runForestAOD_PbPb_DATA_75X.py'
config.JobType.maxMemoryMB = 2500
#config.JobType.inputFiles = ['btagnew_data75X.db']

config.section_("Data")
#config.Data.inputDataset = '/GenericTTbar/HC-CMSSW_7_0_4_START70_V7-v1/GEN-SIM-RECO'
#config.Data.lumiMask = 'Cert_262081-262328_5TeV_PromptReco_Collisions15_25ns_JSON.txt'
config.Data.lumiMask = "Cert_262548-263757_PromptReco_HICollisions15_JSON_v2_part1.txt"
#config.Data.userInputFiles = open('HighPtJet80_ppRECO.txt').readlines()
config.Data.inputDataset = '/HIHardProbes/HIRun2015-PromptReco-v1/AOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 1
#config.Data.outLFNDirBase = '/store/group/phys_heavyions/ginnocen/Djetstudy'
config.Data.publication = False
config.section_("Site")
config.Site.storageSite = 'T2_US_MIT'
config.Site.ignoreGlobalBlacklist = True
#config.Site.whitelist = 'T2_US_MIT'

