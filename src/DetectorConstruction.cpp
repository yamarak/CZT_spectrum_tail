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
/// \file DetectorConstruction.cpp
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.h"

#include <G4VPhysicalVolume.hh>
#include <G4LogicalVolume.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4PhysicalConstants.hh>

DetectorConstruction::DetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	auto* man = G4NistManager::Instance();
	auto* air = man->FindOrBuildMaterial("G4_AIR");
	auto* CdZnTe = new G4Material("CADMIUM_ZINC_TELLURIDE",
								  5.78 * g / cm3,
								  3,
								  kStateSolid);
	CdZnTe->AddElement(man->FindOrBuildElement("Cd"), 9);
	CdZnTe->AddElement(man->FindOrBuildElement("Zn"), 1);
	CdZnTe->AddElement(man->FindOrBuildElement("Te"), 10);

	const G4double world_hx{ 1 * cm };
	const G4double world_hy{ 1 * cm };
	const G4double world_hz{ 1 * cm };

	auto* worldBox = new G4Box("World", world_hx, world_hy, world_hz);
	auto* worldLog = new G4LogicalVolume(worldBox, air, "World");
	auto* worldVol = new G4PVPlacement(nullptr,
									   G4ThreeVector(),
									   worldLog,
									   "World",
									   nullptr,
									   false,
									   0);

	const G4double crystal_hs{ 2.5 * mm };

	auto* crystalBox = new G4Box("Crystal",
								 crystal_hs, crystal_hs, crystal_hs);
	auto* crystalLog = new G4LogicalVolume(crystalBox,
										   CdZnTe,
										   "Crystal");
	new G4PVPlacement(nullptr,
					  G4ThreeVector(),
					  crystalLog,
					  "Crystal",
					  worldLog,
					  false,
					  0,
					  true);

	return worldVol;
}
