/** @file	vrpn_Tracker_WiimoteHead.h
	@brief	vrpn_Tracker interface provided by processing Wii Remote data
	for head tracking.

	@date	2009-2010

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/
/*
	Copyright Iowa State University 2009-2010
	Distributed under the Boost Software License, Version 1.0.
	(See accompanying comment below or copy at
	http://www.boost.org/LICENSE_1_0.txt)

	Boost Software License - Version 1.0 - August 17th, 2003

	Permission is hereby granted, free of charge, to any person or organization
	obtaining a copy of the software and accompanying documentation covered by
	this license (the "Software") to use, reproduce, display, distribute,
	execute, and transmit the Software, and to prepare derivative works of the
	Software, and to permit third-parties to whom the Software is furnished to
	do so, all subject to the following:

	The copyright notices in the Software and this entire statement, including
	the above license grant, this restriction and the following disclaimer,
	must be included in all copies of the Software, in whole or in part, and
	all derivative works of the Software, unless such copies or derivative
	works are solely in the form of machine-executable object code generated by
	a source language processor.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
	SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
	FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.
*/

#ifndef __TRACKER_WIIMOTEHEAD_H
#define __TRACKER_WIIMOTEHEAD_H

#include "vrpn_Tracker.h"
#include "vrpn_Analog.h"
#include <quat.h>

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _WIN32
#include <sys/time.h>
#endif

// The time reported by this tracker is as of the last report it has had
// from the Wiimote, to ensure accurate timing.
class VRPN_API vrpn_Tracker_WiimoteHead : public vrpn_Tracker {
	public:
	vrpn_Tracker_WiimoteHead (const char* name,
				  vrpn_Connection * trackercon,
				  const char* wiimote,
				  float update_rate);

	virtual ~vrpn_Tracker_WiimoteHead (void);

	void setupWiimote();

	virtual void mainloop();
	virtual void reset(void);

	void report();

	static int VRPN_CALLBACK handle_connection (void*, vrpn_HANDLERPARAM);
	static int VRPN_CALLBACK handle_dropLastConnection (void*, vrpn_HANDLERPARAM);

	long needwiimote_m_id;
	long refreshwiimote_m_id;
	long wmheadtrackserver_s_id;

	protected:

	struct timeval  d_prevtime;     //< Time of the previous report
	const double          d_update_interval; //< How long to wait between sends
	const double				d_blobDistance;

	enum FlipState {
		FLIP_NORMAL,
		FLIP_180,
		FLIP_UNKNOWN
	};

	FlipState d_flipState;

	double d_vX[4];
	double d_vY[4];
	double d_vSize[4];
	double d_points;

	bool d_contact;
	bool d_lock;
	bool d_updated;
	bool d_needWiimote;

	vrpn_Analog_Remote* d_ana;
	const char* d_name;

	q_xyz_quat_type d_gravityXform;
	q_type d_flip;
	q_xyz_quat_type d_currentPose;
	q_vec_type d_vSensorZAxis;

	bool		d_gravDirty;
	q_vec_type	d_vGravAntepenultimate;
	q_vec_type	d_vGravPenultimate;
	q_vec_type	d_vGrav;

	bool	register_custom_types();
	void    update_pose(double time_interval);
	void    convert_pose_to_tracker(void);

	vrpn_bool shouldReport(double elapsedInterval) const;
	bool haveGravity() const;

	static void VRPN_CALLBACK handle_analog_update(void* userdata, const vrpn_ANALOGCB info);
	static void VRPN_CALLBACK handle_refresh_wiimote(void* userdata, const vrpn_ANALOGCB info);

};

#endif
