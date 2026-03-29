

#include "ThunderTrailEffect.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"

AThunderTrailEffect::AThunderTrailEffect()
{
	PrimaryActorTick.bCanEverTick = true;
	//プレイヤーの移動が終わった後に位置を更新する
	//Tickグループを「TG_PostUpdateWork」に設定
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	RootComponent = NiagaraComp;
	NiagaraComp->SetAutoActivate(true);
}

void AThunderTrailEffect::BeginPlay()
{
	Super::BeginPlay();

	//生成された瞬間の座標と回転を記録
	StartLocation = GetActorLocation();
	FixedRotation = GetActorRotation();

	//エフェクトは水平方向にのみ伸ばす
	FixedRotation.Pitch = 0.0f;
	FixedRotation.Roll = 0.0f;
}

void AThunderTrailEffect::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	//フェードアウト処理
	if (bIsFinished)
	{
		//現在のスケール
		FVector CurrentScale = GetActorScale3D();
		
		float NewThickness = FMath::FInterpTo(CurrentScale.Y, 0.0f, DeltaTime, FadeOutInterpSpeed);

		SetActorScale3D(FVector(CurrentScale.X, NewThickness, NewThickness));

		return;
	}

	//プレイヤーへの追従と伸長処理
	AActor* Parent = GetAttachParentActor();

	if (Parent)
	{
		//開始地点開始アングルに固定
		SetActorLocation(StartLocation);
		SetActorRotation(FixedRotation);

		//距離計算
		FVector CurrentPlayerPos = Parent->GetActorLocation();

		//進行方向へ
		FVector MoveVector = CurrentPlayerPos - StartLocation;

		//エフェクトの正面方向ベクトル
		FVector ForwardVector = FRotationMatrix(FixedRotation).GetUnitAxis(EAxis::X);
		
		//エフェクトの正面方向成分
		float ForwardDistance = FVector::DotProduct(MoveVector, ForwardVector);

		//後ろに下がった場合マイナススケールで
		if (ForwardDistance < 0.0f) ForwardDistance = 0.0f;

		//スケール適用
		FVector NewScale = FVector(ForwardDistance / BaseEffectLength, ThicknessScale, ThicknessScale);
		SetActorScale3D(NewScale);
	}
}

void AThunderTrailEffect::BeginFadeOut()
{
	if (bIsFinished) return;

	bIsFinished = true;

	//プレイヤーから切り離しその場に残留
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	//指定時間後に破棄
	SetLifeSpan(FadeOutLifeSpan);
}

