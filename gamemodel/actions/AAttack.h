/*
 * AAttack.h
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#ifndef AATTACK_H_
#define AATTACK_H_

#include <boost/shared_ptr.hpp>

#include "../GameAction.h" // <-- Mit "" sucht der Compiler immer von der aktuellen Datei aus
#include <gamemodel/entities/EPlace.h> // <-- Mit <> immer im Include-Path, also C:/MinGW/include oder auch ...../UH-Inf-StrategicGame/
#include <gamemodel/utils/coordinates.h>

class AAttack: public GameAction {
public:
	AAttack();
	virtual ~AAttack();

	coordinates where; // Ich weiﬂ, wo das Problem liegt: Der versucht immer 'where' zu initialisieren. Da der
	// Compiler nichts weiter dazu weiﬂ, versucht er es mit eine Konstruktor ohne Argumente. Was aber nicht geht
	// weil:
};

typedef boost::shared_ptr<AAttack> AAttackPtr;

#endif /* AATTACK_H_ */
