//#define RIGHTFACE
//#define DEMOMODE
#include <Arduino.h>
//--------------- ANIMATIONS ---------------
//#include "Animation\ProtoDRMorphAnimation.h"

//#include "Animation\Commissions\VesperAnimation.h"
//#include "Animation\KaiborgV1Animation.h"
//#include "Animation\ProtoV3Animation.h"
//#include "Animation\FullScreenAnimation.h"
//#include "Animation\VectorFieldAnimation.h"
//#include "Animation\CoelaBonkAnimation.h"
//#include "Animation\FoxAnimation.h"
//#include "Animation\SpyroAnimation.h"
//#include "Animation\SpyroRotateAnimation.h"
//#include "Animation\PikachuAnimation.h"
//#include "Animation\BeeAnimation.h"
//#include "Animation\ProtogenArtleckAnimation.h"
//#include "Animation\ProtogenHUB75Animation.h"
//#include "Animation\DeltaruneAnimation.h"
//#include "Animation\NukudeFaceAnimation.h"
//#include "Animation\Commissions\WaffleDaProtoAnimation.h"

//--------------- CONTROLLERS ---------------
//#include "Controllers\KaiborgV1Controller.h"
//#include "Controllers\altPins-KBV1D1.h"
//#include "Controllers\ProtoDRController.h"

#include "Controllers\Meteor(KBV1D1)Controller.h"
//#include "Animation\ProtogenKitFaceAnimation.h"

#include "Sensors\SerialSync.h"
SerialSync transfer = SerialSync();

//#include "Signals\FFTVoiceDetection.h"


uint8_t maxBrightness = 80;

/* #ifdef RIGHTFACE
ProtoDRController controller = ProtoDRController(maxBrightness, ProtoDRController::RIGHT);
#else
ProtoDRController controller = ProtoDRController(maxBrightness, ProtoDRController::LEFT);
#endif
*/
//#include "Animation\protokitStandard.h"
MeteorV1D1Controller controller = MeteorV1D1Controller(maxBrightness);
//ProtogenKitFaceAnimation animation = ProtogenKitFaceAnimation();


//#include "Controllers\KaiborgV1D1Controller.h"
#include "Animation\MeteorFaceAnimation.h"
//KaiborgV1D1Controller controller = KaiborgV1D1Controller(maxBrightness);
MeteorFaceAnimation animation = MeteorFaceAnimation();

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
   
  transfer.Initialize();
  transfer.SetDead(false);
  transfer.Send();

    controller.Initialize();
}

void loop() {
    float ratio = (float)(millis() % 5000) / 5000.0f;
    controller.SetAccentBrightness(animation.GetAccentBrightness() * 25 + 5);
    controller.SetBrightness(powf(animation.GetBrightness() + 3, 2) / 3);
    //controller.SetBrightness(transfer.GetBrightness());
Serial.println("cont brightness: "+String(powf(animation.GetBrightness() + 3, 2) / 3));
Serial.println("serial brightness: "+transfer.GetBrightness());
    //animation.SetCameraMirror(false);
    animation.UpdateTime(ratio);
    controller.RenderCamera(animation.GetScene(), 0);

    //animation.SetCameraMirror(true);
    animation.UpdateTime(ratio);
    controller.RenderCamera(animation.GetScene(), 1);
    controller.Display();

    Serial.print("Animated in ");
    Serial.print(animation.GetAnimationTime(), 4);

    Serial.print("s, Rendered in ");
    Serial.print(controller.GetRenderTime(), 4);
    Serial.println("s");

    transfer.Read();
    Serial.println("reading transfer...");
    
}
