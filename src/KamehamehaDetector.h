//@COPYRIGHT@//
//
// Copyright (c) 2011, Tomoto S. Washio
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of the Tomoto S. Washio nor the names of his
//     contributors may be used to endorse or promote products derived from
//     this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TOMOTO S. WASHIO BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//@COPYRIGHT@//

#ifndef _KAMEHAMEHA_DECECTOR_H_
#define _KAMEHAMEHA_DETECTOR_H_

#include "common.h"
#include "Configurable.h"
#include "AbstractPoseDetector.h"
#include "KamehamehaStatus.h"
#include "KamehamehaRenderer.h"
#include "HenshinDetector.h"
#include "TimeTicker.h"
#include <list>

class KamehamehaDetector : public AbstractPoseDetector, Configurable
{
private:
	KamehamehaStatus* m_status;
	KamehamehaRenderer* m_kkhRenderer;

	struct TimeVectorEntry {
		float dt;
		XV3 v;

		TimeVectorEntry(float dt, const XV3& v) { this->dt = dt, this->v = v; }
	};
	std::list<TimeVectorEntry> m_forwardVectorHistory;

public:
	KamehamehaDetector(HenshinDetector* henshinDetector, KamehamehaStatus* status, KamehamehaRenderer* kkhRenderer);
	virtual ~KamehamehaDetector();

	//
	// posing detector methods
	//

	virtual bool isPosing(float dt);
	virtual void onPoseDetected(float dt);
	virtual void onDetectPost(float dt);

private:
	void transitTo(KamehamehaStatus::Stage stage);
	void updateGeometry(const XV3& center, const XV3& base);
	void updatePoseGrowth(float dt);
	void updateForwardVectorHistory(float dt);
	float getMotionIntensity();

	float getHandDistanceThreshold();
	float getArmStraightThreshold();
	float getArmLevelThreshold();
	float getMotionIntensityFactor();
};

#endif
