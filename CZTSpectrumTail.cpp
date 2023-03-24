//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file CZTSpectrumTail1.cpp
/// \brief Main program of the CZTSpectrumTail.
/// Defines the entry point for the application.
//

#include "DetectorConstruction.h"
#include "ActionInitialization.h"

#include <G4RunManagerFactory.hh>
#include <QBBC.hh>
#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
#include <G4VisExecutive.hh>

using namespace std;

int main(int argc, char** argv)
{
	auto* runManager = G4RunManagerFactory::CreateRunManager();

	runManager->SetUserInitialization(new DetectorConstruction);
	runManager->SetUserInitialization(new QBBC);
	runManager->SetUserInitialization(new ActionInitialization);

	runManager->Initialize();

	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	auto* UImanager = G4UImanager::GetUIpointer();

	if (argc == 1)
	{
		auto* ui = new G4UIExecutive(argc, argv);
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}
	else
	{
		G4String fileName = argv[1];
		UImanager->ApplyCommand("/control/execute " + fileName);
	}

	delete visManager;
	delete UImanager;
	return 0;
}
