#include "PlantModel.h"
/*provide an struct myjoint 
  need to call Init_myjoint first
	*/
#ifdef NEW_SHELINDER
	struct MYJOINT myjoint={
		.Psource=301325,
		.rotaryPlate={
			.r=0.06,
			.m=0.943,//0.523,
			.com=0.11,
			.I=0.034566,//8.29e-4,
			.b=0,
			.fm=0.005,
			.fc=0.2,
			.kv=0.01},
		.shelinder1={
			.lmax=0.1,
			.x0=0.2,
			.v0=5e-6,
			.A=2.2e-3,
			.m=0.025,
			.k=800,
			.b=1,
			.fm=8,
			.fc=8,
			.kv=0.02
			},
		.shelinder2={
			.lmax=0.1,
			.x0=0.2,
			.v0=5e-6,
			.A=2.2e-3,
			.m=0.025,
			.k=800,
			.b=1,
			.fm=8,
			.fc=8,
			.kv=0.02},
	};
#else
	struct MYJOINT myjoint={
		.Psource=201325,
		.rotaryPlate={
			.r=0.08,
			.m=1.11,
			.com=0.06,
			.I=0.0155,
			.b=0,
			.fm=0.005,
			.fc=0.2,
			.kv=0.01},
		.shelinder1={
			.lmax=0.2,
			.x0=0.2,
			.v0=5e-6,
			.A=2.2e-3,
			.m=0.01,
			.k=400,
			.b=1,
			.fm=10,
			.fc=10,
			.kv=0.02},
		.shelinder2={
			.lmax=0.2,
			.x0=0.2,
			.v0=5e-6,
			.A=2.2e-3,
			.m=0.01,
			.k=400,
			.b=1,
			.fm=10,
			.fc=10,
			.kv=0.02},
	};
#endif




void Init_myjoint()
{
	myjoint.I=myjoint.rotaryPlate.I+(myjoint.shelinder1.m+myjoint.shelinder2.m)*myjoint.rotaryPlate.r*myjoint.rotaryPlate.r;
	myjoint.B=myjoint.rotaryPlate.b+(myjoint.shelinder1.b+myjoint.shelinder2.b)*myjoint.rotaryPlate.r*myjoint.rotaryPlate.r;
    myjoint.K=(myjoint.shelinder1.k+myjoint.shelinder2.k)*myjoint.rotaryPlate.r*myjoint.rotaryPlate.r;
}
