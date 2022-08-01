#pragma once
#include "playerbase.h"


class Door;

// vtable at 021284E0 (ov10)
class Player : public PlayerBase
{
public:

	using StateFunction = bool (Player::*)(void*);

	struct ShootCannonArg {

		fx32 curveForce;
		fx32 unused4;
		s16 curveAngle;
		s16 direction;

	};

	struct BumpedArg {

		Vec2 velocity;
		s16 angle;

	};

	struct PlayerBumpArg {

		Vec2* velocity;
		bool32 groundPounded;

	};

	struct FireworkParam {

		fx32 x;
		fx32 y;
		fx32 radius;

	};

	enum class FrameMode : u32
	{

		Restart,
		Continue,
		Custom

	};

	enum class ColliderPushSide : u32
	{

		Down	= 0x1,
		Up		= 0x2,
		Right	= 0x4,
		Left	= 0x8

	};

	enum class PipeType {

		Down,
		Right,
		Up,
		Left

	};

	enum class DoorType {

		Standard,
		Mini,
		Boss

	};

	enum class PowerupScaleAnimType : s8
	{

		SmallToSuper,
		SuperToSmall,
		MiniToSmall,
		SmallToMini,
		MiniToSuper,
		SuperToMini,
		SuperToSuper // No effect

	};


	void setAnimation(u32 id, bool doBlend, FrameMode frameMode, fx32 speed, u16 frame = 0);
	void setCapAnimation();
	void setupCarryPartialAnimation(bool throwing);
	void updateAnimation();
	bool isBodyAnimationCompleted() const;
	void setBodyAnimationFrame(u16 frame);
	u16 getBodyAnimationFrame() const;
	void setBodyAnimationSpeed(fx32 speed);
	fx32 getBodyAnimationSpeed() const;
	bool isBodyAnimationPassing(s16 frame) const;
	void setHeadAnimation(u32 id);

	void playPowerupSound();
	void switchPowerupModel();
	void switchBodyAnimations(u32 sourceModel, u32 targetModel);
	void powerupApplied();
	void disableTransitParticles();
	bool updatePowerupGain();
	void switchFromMega();
	void megaShrunk();
	bool updateMegaShrinking();
	bool updatePowerupApplied();
	void growToMega();
	bool updateMegaGrowing();
	u32 updatePowerupScaleAnimation();
	void preparePowerupSwitch();
	bool updatePowerupSwitch();
	void revertMegaGrowing(fx32 animationFrame);
	bool updateMegaRevert();
	bool updatePowerupState();
	void switchPowerupDirect(PowerupState powerup);

	void spawnPipeUp();
	void spawnPipeDown();
	void spawnPipeLeft();
	void spawnPipeRight();
	void spawnMiniPipeUp();
	void spawnMiniPipeDown();
	void spawnMiniPipeLeft();
	void spawnMiniPipeRight();
	void spawnDoor();
	void spawnDoor14();
	void spawnDoor15();
	void spawnVSPipe();
	void spawnJumping();
	void spawnVine();
	void beginCutscene(bool castleBoss);
	void endCutscene();
	void beginBossDefeatCutscene();
	void enterTransition();
	void tryLeaveTransition();
	void transitWorldCannon(const ShootCannonArg* arg);
	void transitTurntable();
	void transitVictory();
	void transitFlagpoleWait();
	void signalFlagpoleWait();
	void updateTransitCollision();
	void spawnDefault();
	void spawnFalling();
	void endJumpTransition();
	void endVineTransition();
	bool switchTransitionState(StateFunction function, void* arg = nullptr);
	bool updateTransitionState();
	bool tryTransitVersusComplete();
	bool tryTransitVersusDummy();
	void transitMegaShrink();
	bool defaultTransitState(void* arg);
	void transitPipeExit(PipeType type);
	bool enterPipeDownTransitState(void* arg);
	bool crawlPipeDownTransitState(void* arg);
	void beginExitPipeUpTransition();
	bool exitPipeUpTransitState(void* arg);
	bool enterPipeUpTransitState(void* arg);
	bool crawlPipeUpTransitState(void* arg);
	void beginExitPipeDownTransition();
	bool exitPipeDownTransitState(void* arg);
	bool enterPipeRightTransitState(void* arg);
	bool crawlPipeRightTransitState(void* arg);
	void beginExitPipeLeftTransition();
	bool exitPipeLeftTransitState(void* arg);
	bool enterPipeLeftTransitState(void* arg);
	bool crawlPipeLeftTransitState(void* arg);
	void beginExitPipeRightTransition();
	bool exitPipeRightTransitState(void* arg);
	void beginEnterDoorTransition(DoorType door);
	void enterDoorOpen();
	void enterDoorWalk();
	void enterDoorClose();
	bool enterDoorTransitState(void* arg); // arg = (DoorType type)
	void beginExitDoorTransition();
	void beginExitStandardDoorTransition();
	void beginExitMiniDoorTransition();
	void beginExitBossDoorTransition();
	bool exitDoorTransitState(void* arg); // arg = (DoorType type)
	void beginVSPipeTransition();
	bool vsPipeTransitState(void* arg);
	bool warpZoneTransitState(void* arg);
	void beginJumpTransition();
	bool jumpTransitState(void* arg);
	void beginVineTransition();
	bool vineTransitState(void* arg);
	u32 playGoalFanfare(); // Returns the stage timer's ones digit
	void goalSpawnFireworks();
	void goalMegaClear();
	bool flagpoleTransitState(void* arg);
	bool flagpoleWaitTransitState(void* arg);
	bool versusTimesUpTransitState(void* arg);
	bool versusCompleteTransitState(void* arg);
	bool versusDummyTransitState(void* arg);
	bool bowserJrVictoryTransitState(void* arg);
	bool cutsceneTransitState(void* arg);
	bool bossCutsceneTransitState(void* arg);
	bool bossDefeatTransitState(void* arg);
	bool bossVictoryTransitState(void* arg);
	bool inactiveTransitState(void* arg); // arg = (bool* playerVisible)
	bool shootWorldCannonTransitState(void* arg); // arg = (ShootCannonArg* arg)
	// 02119E7C
	bool turntableTransitState(void* arg);
	bool unusedVictoryTransitState(void* arg);
	void beginDeathTransition();
	bool standardDeathTransitState(void* arg);
	bool lavaDeathTransitState(void* arg);
	bool poisonDeathTransitState(void* arg);
	bool pitDeathTransitState(void* arg);
	void transitEntranceWarp(EntranceType type);
	void beginEntrancePose(EntranceType type);
	void transitEntranceSpawn(EntranceType type);
	void beginEntranceTransition(EntranceType type);
	void purgeInactiveActors();
	bool viewTransitState(void* arg); // TODO: document usage and better name
	bool areaTransitState(void* arg); // TODO: document usage and better name
	void updateStepParticles();
	void beginUnusedVictoryTransition();
	bool unusedVictoryWalk();
	void unusedVictoryBeginTurn();
	bool transitTurn();
	void unusedVictoryBeginJump();
	bool unusedVictoryUpdateJump();
	void transitJump();
	void transitSpawnJump();
	bool transitUpdateJump();
	void cutsceneBeginIdlePose();
	void goalBeginPoleGrab();
	bool goalPoleGrabCompleted();
	void goalBeginPoleSlide();
	bool goalPoleSlideCompleted();
	void goalBeginPoleWait();
	bool goalPoleTurn();
	bool transitStepCompleted();
	void goalBeginPoleJump();
	bool cutsceneUpdateJump();
	void goalBeginJumpLand();
	bool goalJumpLandCompleted();
	void goalFaceCamera();
	void goalBeginRemoveCap();
	bool goalUpdatePutCap();
	bool goalUpdateRemoveCap();
	void goalBeginMegaClear();
	bool goalMegaClearCompleted();
	void bossBeginVictoryPose();
	void bowserJrBeginVictoryPose();
	void bossBeginWaitPeach();
	void bossBeginRemoveCap();
	bool bossUpdateRemoveCap();
	void bossBeginPeachKiss();
	bool bossPeachKissCompleted();
	void bossBeginPeachKissed();
	bool bossPeachKissedCompleted();
	void cutsceneSetWalkAnimation(bool shellSlide);
	void cutsceneBeginWalk(bool shellSlide);
	bool cutsceneUpdateWalk(bool shellSlide);
	bool transitAdjustPipePositionX(fx32 step);
	bool transitAdjustPipePositionX(fx32 step, fx32 target);
	bool transitAdjustPipePositionY(fx32 step, fx32 target);
	void transitBeginConnectedPipe();
	bool transitUpdateConnectedPipe(u16& targetDirection);
	void deathBeginDeadPose();
	bool deathPoseCompleted();
	void deathBeginFlight();
	bool deathUpdateFlight();
	void bossBeginCallPeach();
	void bossBeginStarePeach();
	void bossBeginReactPeach();
	void bossUpdateDash();
	void bossBeginChasePeach();
	bool bossUpdateChasePeach();
	bool bossWalkToSwitch();
	void switchMegaWalkAnimation(fx32 speed);
	void switchMegaAnimation(fx32 speed);
	void beginIdleAnimation(bool doBlend, fx32 speed);
	void updateCommonAnimations(bool doBlend, bool unk);
	void transitBeginIdlePose(bool doBlend);

	void setPerspectivePosition(s16 rotation, fx32 scale, const Vec3& position);

	static void activeCallback(ActiveCollider& self, ActiveCollider& other);
	static void specialActiveCallback(ActiveCollider& self, ActiveCollider& other);
	void setSpecialColliderCallback();

	Player();
	~Player();

	void setX(fx32 x) override;
	void moveX(fx32 offset) override;
	bool adjustPosition();
	void setHorizontalVelocity(fx32 velocity);
	void setVerticalVelocity(fx32 velocity);

	void fetchPowerupParams();
	void setupColliderPowerup();
	void setupCollisionMgr(bool switchingPowerup);

	void setJumpFallAccel();
	void setJumpFallAccelNormal();
	void smoothRotationY(s32 end, fx32 ratio);

	bool carry(StageActor& actor) override;
	bool hangMiniToCeiling(StageActor& actor) override;
	bool dropMiniFromCeiling() override;
	bool hangToCeiling(StageActor& actor) override;
	bool dropFromCeiling() override;
	bool waitInCannon(StageActor& cannon, const Vec3& position, s16 angleX, s16 angleY) override;
	void updateCannonTransform(const Vec3& position, s16 angleX, s16 angleY);
	bool shootFromCannon(StageActor& cannon, fx32 curveForce, s16 curveAngle, s16 direction, bool32 worldCannon) override;
	bool grabPendulum() override;

	bool doJumpEx(fx32 force, u16 duration, u8 lockHorizontalDuration, bool playSFX, bool noConsecutive, s8 variation) override;
	bool doJump(fx32 force, u16 duration, bool playSFX, bool noConsecutive, s8 variation) override;
	// 02105338
	bool tryJump(fx32 force, u16 duration, bool playSFX, bool noConsecutive, s8 variation);
	bool doSpinJump(fx32 force) override;
	bool trySpinJump(const SpinJumpState& jump);
	bool trySpinBlockJump();
	bool doBounceWhirl() override;
	bool doTornadoWhirl() override;

	void releaseHorizontalKeys();
	void losePowerup();
	void onEntityBump(StageActor& actor, fx32 velocityX, fx32 velocityY);
	void releaseHeldActor();
	void tryReleaseHeldActor();
	bool damage(StageActor& actor, fx32 velocityX, fx32 velocityY, PlayerDamageType type);
	bool dealDamage(StageActor& actor, fx32 velocityX, fx32 velocityY, PlayerDamageType type) override;

	bool tryCrouch() override;
	bool tryBump(const Vec2& velocity) override;
	bool tryPlayerBump(const Vec2& velocity) override;
	bool doPlayerBump(const Vec2& velocity, bool groundPounded) override;
	bool doBump(const Vec2& velocity) override;
	bool doBossBump(const Vec2& velocity);

	bool isNotClimbing() override; // TODO: Also checks for a pipe cannon state/flag??
	void grabFlagpole(const Vec3& position);
	bool trySlide() override;

	void endDeathTransition();
	void setMiniWaterWalk();
	void updateLiquidCollision();
	void applyHorizontalExternalForce();
	void updateCollision(bool damagePlayer) override;
	void tryUpdateCollision(bool unk); // TODO: What does this do other than calling updateCollision()?
	void updatePhysics();
	void updatePosition(const Vec3& position, s16 rotationY, u8 direction) override;

	bool stomp() override; // Stomps the player, possibly unused
	bool tryEnterTransition() override;
	bool trySwim();
	bool tryEnterBossTransition(); // Used only during the Mega Goomba battle
	bool leaveTransition() override;
	void setPerspectiveTransform(fx32 scale, const Vec3s& rotation, const Vec3& position) override;
	s32 virt48() override; // Another transition
	s32 doTurntableTransition() override;
	void doVictoryTransition(u32 playerID) override;
	void setVictoryTarget(fx32 x, fx32 y, fx32 z) override;
	Vec3 getHandsPosition() override;
	void doWarpZoneTransition() override;
	void doDoorTransition(const Vec3& doorPosition) override;
	void setSpinBlock(fx32 positionX, s16 angle) override;

	bool getDoorTrigger() override;
	bool canAccessPipe() const;
	bool getCannonTrigger() override;
	void enterCannon(const Vec3& cannonPosition) override;
	void virt61(const Vec3& position) override; // Similar to enterCannon
	void enterPipeDown(const Vec3& pipePosition) override;

	bool doLightningShock() override;
	bool paralyze() override;
	void setJumpTables(bool higherJump) override;
	bool bury() override;
	bool trySwitchPowerupDirect(PowerupState powerup) override;
	Vec3 getTopSensorPosition() override;
	void onOneUpCollected() override;

	bool tryDisableMegaPower();
	void disableMegaPower();
	bool crushMegaCeiling();
	bool crushCeiling();
	bool crushMegaGround();
	bool crushGround();
	bool crushMegaLeftWall();
	bool crushLeftWall();
	bool crushMegaRightWall();
	bool crushRightWall();

	void updateMainLogic(); // Does way too many things to be proper name
	bool applyTileDamage();

	bool switchMainState(StateFunction function, void* arg = nullptr);
	bool updateMainState();
	void setMovementState(StateFunction function);
	void updateMovementState();
	void setMetaState(StateFunction function);
	void updateMetaState();

	bool onPrepareResources() override;

	void tryUpdateLayerPosition();
	void updateLayerPosition();
	void reset();
	s32 onCreate() override;
	void updateFirstLiquidCollision();
	bool updateTimesUpTransitions();
	void updatePhysicsLayer();
	void updateSpecialCollider();
	void updateFenceSlamCollider();
	bool updatePowerupTimers(); // TODO: Better name perhaps
	void updateOneUpParticles();
	void updateSmokeParticles();
	void updateSlipperySkidParticles();
	void updateSlipperySlideParticles();
	void updateMegaSlideParticles();
	void spawnMegaLandParticles();
	void spawnTripleJumpLandParticles();
	void spawnGroundPoundLandParticles();
	void spawnWaterLandParticles();
	void trySpawnWaterLandParticles();
	void spawnMegaWaterLandParticles();
	void trySpawnMegaWaterLandParticles();
	void emptyTransitFunc(); // Does nothing
	void udpateLiquidParticles();
	void emptyBumpFunc(); // Does nothing
	void updateLavaFireParticles();
	void updateElectrocutionParticles();
	bool isStepping();
	void updateWalkParticles();
	void updateWaterWalkingParticles();
	void updateWaterWalkingParticlesLeft();
	void updateWaterWalkingParticlesRight();
	void spawnFenceHitParticles(const Vec3& position);
	void spawnWallJumpParticles(const Vec3& position, u8 direction);
	void updateWallSlideParticles(const Vec3& position, u8 direction);
	void spawnSpinJumpStarParticles();
	void updateDrillSpinParticles();
	void spawnDrillSpinWhirlParticles();
	void spawnMegaGrowParticles();
	void spawnQuicksandParticles();
	void spawnFireworkParticles(const Vec3& position);
	void spawnHandSmokeParticles();
	void updateStarParticles();
	void updateMegaParticles();
	void updateStompAnimation();
	void updateActionTimers();
	void updateLookAtHeadRotation();
	s32 onUpdate() override;
	bool updateCarryPartialAnimation();
	// 020FD114
	void playJumpSFX();
	void renderModel();
	void renderModel(bool skip);
	s32 onRender() override;
	void onCleanupResources() override;
	s32 onDestroy() override;


	static constexpr u16 objectID = 21;

	static constexpr u16 updatePriority = objectID;
	static constexpr u16 renderPriority = 28;

	static const ActorProfile profile;


	Door* door;
	Door* bossDoor;
	fx32* jumpTable1;
	fx32* jumpTable2;

	LineSensorH topSensor;
	LineSensorH botSensor;
	LineSensorV sideSensor;
	LineSensorV climbSensor;

	ActiveCollider specialCollider;
	PendulumController pendulum;
	VictoryState victoryState;
	ProgressBarObject progressBarObject;

	Vec3s unk914;
	Vec3s unk920;
	Vec3 entrancePosition;
	Vec3 unk93C;
	Vec3 externalForce;
	Vec2 hitboxPosition;
	Vec2 unk968;
	Vec2 connectedPipeStep;

	StateFunction mainState;
	StateFunction prevMainState;
	StateFunction transitionState;
	StateFunction movementState;
	StateFunction metaState;

	FrameMode modelFrameMode;
	bool32 modelBlendFlag;
	s32 zLayer;
	u32 headAnimID;
	s32 groundRemovedTimer;
	u32 pipeType;
	u32 prevAnimID;
	ColliderPushSide colliderPushSides;
	TileType bottomTileType;
	TileType lastBottomTileType;

	EmitterT unusedEmitter1;
	EmitterT lavaFireEmitter;
	EmitterT unusedEmitter2;
	EmitterT unusedEmitter3;
	EmitterT smallElectricCircularSparksEmitter;
	EmitterT smallElectricStraightSparksEmitter;
	EmitterT smallElectricFlashingStarsEmitter;
	EmitterT smallElectricLightFlashEmitter;
	EmitterT electricCircularSparksEmitter;
	EmitterT electricStraightSparksEmitter;
	EmitterT electricFlashingStarsEmitter;
	EmitterT electricLightFlashEmitter;
	EmitterT unusedEmitter4;
	EmitterT starmanLightStarsEmitter;
	EmitterT starmanDenseStarsEmitter;
	EmitterT rightWallSlideSmokeEmitter;
	EmitterT leftWallSlideSmokeEmitter;
	EmitterT miniWindForceEmitter;
	EmitterT miniWindTwirlEmitter;
	EmitterT windForceEmitter;
	EmitterT windTwirlEmitter;
	EmitterT cannonSmokeEmitter;
	EmitterT rightSnowDustEmitter;
	EmitterT leftSnowDustEmitter;
	EmitterT rightSandDustEmitter;
	EmitterT leftSandDustEmitter;
	EmitterT miniWaterWalkDotsLeftEmitter;
	EmitterT miniWaterWalkSplashLeftEmitter;
	EmitterT miniWaterWalkDotsRightEmitter;
	EmitterT miniWaterWalkSplashRightEmitter;
	EmitterT leftSlipWalkDustEmitter;
	EmitterT leftSlipWalkStarsEmitter;
	EmitterT rightSlipWalkDustEmitter;
	EmitterT rightSlipWalkStarsEmitter;
	EmitterT rightSlipSkidDustEmitter;
	EmitterT rightSlipSkidStarsEmitter;
	EmitterT leftSlipSkidForceEmitter;
	EmitterT leftSlipSkidDustEmitter;
	EmitterT leftSlipSkidStarsEmitter;
	EmitterT rightSlipSkidForceEmitter;
	EmitterT slipSlideDustEmitter;
	EmitterT slipSlideStarsEmitter;
	EmitterT rightSmokeLeftEmitter;
	EmitterT rightSmokeRightEmitter;
	EmitterT leftSmokeLeftEmitter;
	EmitterT leftSmokeRightEmitter;
	EmitterT megaBubblesEmitter;
	EmitterT megaWindForceEmitter;
	EmitterT worldCannonSmokeEmitter;
	EmitterT leftWaterSurfaceSwimMegaSplashEmitter;
	EmitterT rightWaterSurfaceSwimMegaSplashEmitter;
	EmitterT leftWaterSurfaceSwimSplashEmitter;
	EmitterT rightWaterSurfaceSwimSplashEmitter;
	EmitterT leftMegaSlideSmokeEmitter;
	EmitterT rightMegaSlideSmokeEmitter;
	EmitterT megaRightHandLedgeDustEmitter;
	EmitterT megaLeftHandLedgeDustEmitter;
	EmitterT megaRightFootLedgeDustEmitter;
	EmitterT megaLeftFootLedgeDustEmitter;
	EmitterT ledgeDustEmitter;
	EmitterT oneUpStarsEmitters[3];
	EmitterT oneUpStarsSmallEmitters[3];

	fx32 modelAnimSpeed;
	fx32 powerupScaleStep;
	fx32 modelScale;
	fx32 perspectiveScale;
	fx32 unkAE8;
	fx32 unkAEC;
	fx32 unkAF0;
	fx32 unkAF4;
	fx32 modelWidth;
	fx32 modelHeight;
	fx32 stompScale;
	fx32 cannonDepth;
	fx32 spinBlockPosX;
	fx32 powerupScaleOffset; // TODO: What does this offset? Where is it used?
	fx32 externalForceH;
	fx32 rotatedVelocityX;
	fx32 rotatedVelocityY;
	fx32 rotationCenterX;
	fx32 rotationCenterY;
	fx32 pipeTargetX;
	fx32 pipeTargetY;
	u32 unkB2C;
	u32 unkB30;
	u32 unkB34;
	u32 unkB38;
	fx32 prevAnimSpeed;
	u32 unkB40;
	u32 unkB44;
	u32 pendulumClimbFlags;
	u32 unkB4C;

	union {
		s16 initialAngle;
		s16 animDuration; // When the current animation frame reaches this value, an action is triggered
	};

	u16 pendulumFlags;
	u16 pendulumUnk25;
	u16 pendulumUnk1E;
	s16 unkB58;
	s16 unkB5A;
	s16 unkB5C;
	s16 unkB5E;

	union {
		s16 transitStepTimer;
		s16 transitRotation;
		s16 connectedPipeNodeID;
	};

	s16 connectedPipeLength;
	s16 unkB64;
	s16 unkB66;

	union {
		s16 transitionTimer;
		s16 transitDoorType;
	};

	union {
		s16 fireworksToSpawn;
		s16 cannonSmokeTimer;
	};

	s16 fireworkCount;
	s16 fireworkTimer;
	u16 unkB70;
	u16 unkB72;
	u16 unkB74;
	u16 unkB76;
	s16 unkB78;
	s16 rotationAngle;
	s16 stompTimer;
	s16 groundAngle;
	s16 groundPoundRotateTimer;
	s16 jumpDuration;
	s16 spinBlockAngle;
	s16 unkB86;
	s16 unkB88;
	s16 unkB8A;
	s16 unkB8C;
	s16 spinJumpAngle;
	s16 unkB90;
	s16 oneUpSparkleTimer[3];
	s16 lookAtRotation;
	u16 prevAnimFrame;

	u8 lastDirection;
	u8 modelID;
	s8 mainStateStep;
	u8 unkB9F;
	u8 consecutiveJumps;
	u8 jumpVariation;
	u8 unkBA2;
	u8 unkBA3;
	u8 unkBA4;
	u8 turnVerticalVelocityStep;
	s8 powerupSwitchStep;
	u8 powerupSwitchTimer;
	u8 unkBA8;
	PowerupScaleAnimType powerupScaleAnimType;
	u8 unkBAA;
	u8 unkBAB;
	u8 unkBAC;
	s8 transitionStateStep;
	bool holdingItemFlag;
	bool currentModel;
	u8 unkBB0;
	s8 stompState;
	DamageTileFlags damageTileFlags;
	DamageTileType damageTileType;
	u8 groundSteepness;
	u8 unkBB5;
	u8 textureID;
	u8 runKeyTimer; // goes from 10 to 0
	u8 pipeExitTimer; // goes from 8 to 0, once the player has fully exited the pipe
	u8 unkBB9;
	u8 carryKeyTimer; // goes from 8 to 0
	u8 wallSlideLeftTimer;
	u8 wallSlideRightTimer;
	u8 unkBBD;
	u8 jumpLockHorizontalTimer;
	u8 unkBBF;
	u8 megaParticlesTimer;
	bool forceShrinkMegaSound;
	u8 unkBC2;
	bool jumpFromLedge;
	s8 unkBC4; // "groundpoundRelated"
	u8 unkBC5; // "walkLeftCounter"
	u8 unkBC6; // "walkRightCounter"
	u8 unkBC7;
	u8 groundPoundTimer; // goes from 0 to 3
	bool groundPoundFlag;
	u8 unkBCA;
	bool lookAtActive; // set to true when "LookingAtTarget" is enabled and the player's head rotation is being calculated

};
NTR_SIZE_GUARD(Player, 0xBCC);

using PlayerFrameMode		= Player::FrameMode;
using ColliderPushSide		= Player::ColliderPushSide;
using PlayerPipeType		= Player::PipeType;
using PlayerDoorType		= Player::DoorType;

IMPL_ENUMCLASS_OPERATORS(Player::ColliderPushSide);


// Assumed from 020E3824 (ov10)
NTR_INLINE u8 ActiveCollider::getPlayerID() const {
	return getPlayer()->linkedPlayerID;
}

