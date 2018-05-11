/*
 * trajectoryGeneration.c
 *
 *  Created on: Oct 23, 2017
 *      Author: 40207
 */
#include "trajectoryGeneration.h"
#include <math.h>

//TRAJ_GEN positionTrajectory;
//TRAJ_GEN stiffnessTrajectory;

/*																									 Output  Pointer
 * 					  x0	 x1				 T									v0     			   *x_out   *v_out   *a_out
 * step:		      ori	destination												  Pointer of Outputposition,Outputvelocity, Outputacceleration
 * square:			  ori	amplitude        holdT
 * stepScurve:		  ori	destination      transT	  (x0->x1)
 * squareScurve:	  ori	amplitude        transT   (x0->x1 or x1->-x1)
 * sinoid:			  ori   amplitude        period/4 (0->x1)				    oriv
 */
static void StepInit(TYPE_STEP *s,float x0,float x1,float T);
static void SquareInit(TYPE_SQUARE *s,float x0,float x1,float T);
static void StepScurveInit(TYPE_STEPSCURVE *s,float x0,float x1,float T);
static void SquareScurveInit(TYPE_SQUARESCURVE *s,float x0,float x1,float transT);
static void SinoidInit(TYPE_SINOID *s,float x0,float v0,float x1,float T);

static void StepGenerate(TRAJ_GEN *traj,float t);
static void SquareGenerate(TRAJ_GEN *traj,float t);
static void StepScurveGenerate(TRAJ_GEN *traj,float t);
static void SquareScurveGenerate(TRAJ_GEN *traj,float t);
static void SinoidGenerate(TRAJ_GEN *traj,float t);

static void __StepGenerate(TYPE_STEP *s,float t);
static void __SquareGenerate(TYPE_SQUARE *s,float t);
static void __StepScurveGenerate(TYPE_STEPSCURVE *s,float t);
static void __SquareScurveGenerate(TYPE_SQUARESCURVE *s,float t);
static void __SinoidGenerate(TYPE_SINOID *s,float t);




void InitTraj(TRAJ_GEN *traj,float vaverage)
{
	traj->trajState= TRAJ_GEN_STATE_READY;
	traj->lineType = TRAJ_GEN_STEP;
	traj->vaverage = vaverage;
}




void UpdateTraj(TRAJ_GEN *traj,float xd,uint32_t startTime,uint32_t duration,TRAJ_GEN_CurveTypeDef lineType)
{
	traj->repetition = 1000;
	traj->tStart = startTime;
	traj->trajState = TRAJ_GEN_STATE_BUSY;
	traj->lineType = lineType;

	traj->xd = xd;

	if (lineType == TRAJ_GEN_STEP_SCURVE) {
		traj->tDuration = duration;
		traj->generator = StepScurveGenerate;
		StepScurveInit(&(traj->stepScurve), traj->x0, xd, duration / 1000.0f);
	} else if (lineType == TRAJ_GEN_STEP) {
		traj->tDuration = duration;
		traj->generator = StepGenerate;
		StepInit(&(traj->step), traj->x0, xd, duration / 1000.0f);

	} else if (lineType == TRAJ_GEN_SQUARE) {
		traj->tDuration = duration * traj->repetition;
		traj->tEnd = startTime + duration;
		traj->generator = SquareGenerate;
		SquareInit(&(traj->square), traj->x0, xd, duration / 1000.0f);

	} else if (lineType == TRAJ_GEN_SQUARE_SCURVE) {
		traj->tDuration = duration * traj->repetition;
		traj->generator = SquareScurveGenerate;
		SquareScurveInit(&(traj->squareScurve), traj->x0, xd, duration / 1000.0f);

	} else if (lineType == TRAJ_GEN_SINOID) {
		traj->tDuration = duration * traj->repetition;
		traj->generator = SinoidGenerate;
		SinoidInit(&(traj->sinoid), traj->x0, traj->v0, xd, duration / 1000.0f * 4);
	}
	traj->tEnd = traj->tStart + traj->tDuration;
}
void TrajGen(TRAJ_GEN *traj, uint32_t globalT) {

	if (traj->trajState == TRAJ_GEN_STATE_BUSY) {
		if (globalT > traj->tEnd) {
			traj->trajState = TRAJ_GEN_STATE_READY;
		} else {
			traj->t = globalT - traj->tStart;
			traj->generator(traj, traj->t / 1000.0f);
		}
	}


}


static void StepScurveInit(TYPE_STEPSCURVE *s,float x0,float x1,float T)
{
	float phi;
	float T3=T*T*T;
    float ti;
    float ts;
    int i;
	s->x0 = x0;
	s->x1 = x1;
	s->T = T;
	//dis and J both have sign
	s->dis=x1-x0;
	s->J=32*s->dis/T3*(1.0001+s->LinearProportion);   //the larger LP, the more linear phase and a bigger J.
												   // LP = 0 represents the Min J with no liner phase.
													//1.00001 is to avoid error.
	phi=acos(1-54*s->dis/s->J/T3);
	ti=2*cos((phi+4*M_PI)/3.0);
	ts = T*(ti+1)/6;

	s->_t[0]=0;          //first node
	s->_t[1]=ts;
	s->_t[2]=2*ts;
	s->_t[3]=s->T-2*ts;
	s->_t[4]=s->T-ts;
	s->_t[5]=s->T;		 //last node

	s->_J[0]=s->J;			//first segment
	s->_J[1]=-s->J;
	s->_J[2]=0;
	s->_J[3]=-s->J;
	s->_J[4]=s->J;			//last segment

	//First Node    start rising 1
	s->_x[0]	= s->x0;
	s->_xdot[0]	=	0;
	s->_xddot[0]=	0;

	for(i=1;i<5;i++)
	{
		ti=s->_t[i]-s->_t[i-1];
		s->_x[i] 	= s->_x[i-1] + s->_xdot[i-1]*ti + s->_xddot[i-1]*ti*ti/2 + s->_J[i-1]*ti*ti*ti/6;
		s->_xdot[i]	=			   s->_xdot[i-1] 	+ s->_xddot[i-1]*ti		 + s->_J[i-1]*ti*ti/2;
		s->_xddot[i]=								  s->_xddot[i-1]		 + s->_J[i-1]*ti;
	}
	s->_x[5]	= s->x1;
	s->_xdot[5]	=	0;
	s->_xddot[5]=	0;

}


static void __StepScurveGenerate(TYPE_STEPSCURVE *s,float t)
{
	int i=0;
	while(t>=s->_t[i])
		{
			i++;
			if(i>=6)
				break;
		}
	t=t-s->_t[i-1];
	s->x_out=s->_x[i-1]+s->_xdot[i-1]*t+s->_xddot[i-1]*t*t/2+s->_J[i-1]*t*t*t/6;
	s->v_out=s->_xdot[i-1]+s->_xddot[i-1]*t+s->_J[i-1]*t*t/2;
	s->a_out=s->_xddot[i-1]+s->_J[i-1]*t;
}

static void StepScurveGenerate(TRAJ_GEN *traj,float t)
{
	 __StepScurveGenerate(&(traj->stepScurve),t);
	 traj->x_out = traj->stepScurve.x_out;
	 traj->v_out = traj->stepScurve.v_out;
	 traj->a_out = traj->stepScurve.a_out;

}







static void StepInit(TYPE_STEP *s,float x0,float x1,float T)
{
	s->x0 = x0;
	s->xd = x1;
	s->T = T;   //not used
}


static void __StepGenerate(TYPE_STEP *s,float t)
{
	s->x_out=  s->xd;
	s->v_out=   0;
	s->a_out=   0;
}
static void StepGenerate(TRAJ_GEN *traj,float t)
{
	__StepGenerate(&(traj->step),t);
	 traj->x_out = traj->step.x_out;
	 traj->v_out = traj->step.v_out;
	 traj->a_out = traj->step.a_out;
}


static void SquareInit(TYPE_SQUARE *s,float x0,float x1,float T)
{
	s->x0 = x0;
	s->x1 = x1;
	s->holdT = T;
	s->dir[0]=	(x1>0)?1:-1;
	s->dir[1]=-s->dir[0];
}


static void __SquareGenerate(TYPE_SQUARE *s,float t)
{
	uint8_t seg=((uint32_t)(t/(s->holdT)))%2;
	(s->x_out)=   s->dir[seg]*s->x1;
	(s->v_out)=   0;
	(s->a_out)=   0;
}
static void SquareGenerate(TRAJ_GEN *traj,float t)
{
	__SquareGenerate(&(traj->square),t);
	 traj->x_out = traj->square.x_out;
	 traj->v_out = traj->square.v_out;
	 traj->a_out = traj->square.a_out;
}



static void SquareScurveInit(TYPE_SQUARESCURVE *s,float x0,float x1,float transT)
{
	float holdT = transT*2;
	StepScurveInit(&(s->scurve[0]),x0,x1,transT);
	StepScurveInit(&(s->scurve[1]),x1,-x1,transT);
	StepScurveInit(&(s->scurve[2]),-x1,x1,transT);
	s->x0 = x0;
	s->x1 = x1;
	s->transT = transT;
	s->holdT = holdT;
	s->period = 2*transT+2*holdT;
	s->_t[0]=0;
	s->_t[1]=holdT;
	s->_t[2] = holdT+transT;
	s->_t[3] = 2*holdT+transT;
	s->_t[4] = s->period;

}


static void __SquareScurveGenerate(TYPE_SQUARESCURVE *s,float t)
{
	if(t<s->transT)
	{
		__StepScurveGenerate(&s->scurve[0],t);
		s->x_out = s->scurve[0].x_out;
		s->v_out = s->scurve[0].v_out;
		s->a_out = s->scurve[0].a_out;

	}
	else
	{
		t -= s->transT;
		s->curPeriod = (uint32_t)(t/s->period);
		t -= s->period*s->curPeriod;
		if(t<s->_t[1])
		{
			(s->x_out)=   s->x1;
			(s->v_out)=   0;
			(s->a_out)=   0;
		}
		else if(t<s->_t[2])
		{
			t-=s->_t[1];
			__StepScurveGenerate(&s->scurve[1],t);
			s->x_out = s->scurve[1].x_out;
			s->v_out = s->scurve[1].v_out;
			s->a_out = s->scurve[1].a_out;
		}
		else if(t<s->_t[3])
		{
			(s->x_out)=   - s->x1;
			(s->v_out)=   0;
			(s->a_out)=   0;
		}
		else if(t<s->_t[4])
		{
			t-=s->_t[3];
			__StepScurveGenerate(&s->scurve[2],t);
			s->x_out = s->scurve[2].x_out;
			s->v_out = s->scurve[2].v_out;
			s->a_out = s->scurve[2].a_out;
		}
	}
}
static void SquareScurveGenerate(TRAJ_GEN *traj,float t)
{
	__SquareScurveGenerate(&(traj->squareScurve),t);
	 traj->x_out = traj->squareScurve.x_out;
	 traj->v_out = traj->squareScurve.v_out;
	 traj->a_out = traj->squareScurve.a_out;
}

static void SinoidInit(TYPE_SINOID *s,float x0,float v0,float amp,float periodQuater)
{
	float phival = x0/amp;
	s->x0 = x0;
	s->v0 = v0;
	s->amplitude = amp;
	s->period = periodQuater*4;
	s->frequency = 1/s->period;
	s->omega = 2*M_PI*s->frequency;

	if(phival>=1)
		s->phi = M_PI/2;
	else if(phival<=-1)
		s->phi = -M_PI/2;
	else if(phival>=0){
			if(s->v0 >=0)
				s->phi = asin(phival);
			else
				s->phi = M_PI-asin(phival);
	}
	else{  //(phival<0)
		if(s->v0 <=0)
			s->phi = M_PI+asin(-phival);
		else
			s->phi = 2*M_PI-asin(-phival);
	}

}


static void __SinoidGenerate(TYPE_SINOID *s,float t)
{
	(s->x_out)=   s->amplitude*				   sin(s->omega*t + s->phi);
	(s->v_out)=   s->amplitude* 		  s->omega*cos(s->omega*t + s->phi);
	(s->a_out)= - s->amplitude* s->omega*s->omega*sin(s->omega*t + s->phi);

}

static void SinoidGenerate(TRAJ_GEN *traj,float t)
{
	__SinoidGenerate(&(traj->sinoid),t);
	 traj->x_out = traj->sinoid.x_out;
	 traj->v_out = traj->sinoid.v_out;
	 traj->a_out = traj->sinoid.a_out;
}
