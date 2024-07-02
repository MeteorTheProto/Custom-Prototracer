#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Objects\Background.h"

//face morph object includes
#include "..\Morph\MeteorEye.h"
#include "..\Morph\MeteorFace.h"
#include "..\Morph\MeteorBrow.h"
#include "..\Morph\MeteorBlush.h"


#include "..\Render\Scene.h"
#include "..\Signals\FunctionGenerator.h"
#include "..\Menu\SingleButtonMenu.h"

#include "..\Sensors\APDS9960.h"

#include "..\Materials\Animated\SpectrumAnalyzerMeteor.h"
#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Animated\MeteorSpiral.h"

#include "..\Materials\CombineMaterial.h"

#include "AnimationTracks\BlinkTrack.h"
//#include "KeyFrameTrack.h"

#include "..\Signals\FFTVoiceDetection.h"
#include "..\Sensors\MicrophoneFourier_MAX9814.h"

//#include "..\Flash\ImageSequences\VaporWave.h"

//#include "..\Sensors\SerialSync.h"


//#include "Sensors\SerialSync.h"
#include "..\Sensors\SerialSync.h"



class MeteorFaceAnimation : public Animation<5> {
private:

/**** creates the objects*/

    /** full screen flat panel object */
    Background background;

    /** mouth and nose object */
    MeteorFace face;

    /** eye object */
    MeteorEye eye;

    /** eyebrow object */
    MeteorBrow brow;

    /** blush object */
    MeteorBlush blush;
    
    
   
/**** animator objects */

    /** face (mouth + nose) animator */
    EasyEaseAnimator<18> eEAface = EasyEaseAnimator<18>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);

    /** eye animator */
    EasyEaseAnimator<3> eEAeye = EasyEaseAnimator<3>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);

    /** brow animator */
    EasyEaseAnimator<5> eEAbrow = EasyEaseAnimator<5>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);

    /** blush animator */
    EasyEaseAnimator<4> eEAblush = EasyEaseAnimator<4>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);

/**** Materials */

    /** animated noise overlay/background (defined in RainbowNoise.h) */
    RainbowNoise rainbowNoise;

    /** animated spiral/swirl of Meteor's horn colors (defined in MeteorSpiral.h) */
    MeteorSpiral rainbowSpiral;

    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255,15,15));
    
    /** gadient material */
    RGBColor gradientSpectrum[2] = {RGBColor(225, 225, 0), RGBColor(225, 225, 168)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, true);

    /** solid face color materials */
    SimpleMaterial yellowMat = SimpleMaterial(yellow); //200,200,50
    SimpleMaterial ltYellowMat = SimpleMaterial(ltYellow); //255,200,50
    SimpleMaterial pinkMat = SimpleMaterial(pink);
    SimpleMaterial tealMat = SimpleMaterial(teal); 
    SimpleMaterial purpleMat = SimpleMaterial(purple);
    SimpleMaterial blueMat = SimpleMaterial(blue);
    SimpleMaterial dkBlueMat = SimpleMaterial(dkBlue);

    /** creates a single material comprised of <n> layers */
    CombineMaterial<5> faceMaterial;
    
    /* sets size & position of spectrum anylzer material (defined in SpectrumAnalyzerMeteor.h) */
    SpectrumAnalyzerMeteor sA = SpectrumAnalyzerMeteor(Vector2D(250, 200), Vector2D(120, 100), true, true);

    /*blink track */
    BlinkTrack<1> blink;
    //KeyFrameTrack blink = KeyFrameTrack( 0.0f, 1.0f, KeyFrameTrack::Cosine);
    //Animatio blink = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -1.0f, 1.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -0.5f, 0.5f, 2.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -0.5f, 0.5f, 3.7f);

    APDS9960 boop;
    Menu menuObj;
    //SerialSync transfer;
    //SerialSync serialCom;
    float rainbowFaceMix = 0.0f;
    float angryFaceMix = 0.0f;
    uint8_t rainbowFaceIndex = 50;
    uint8_t angryFaceIndex = 40;

    FFTVoiceDetection<128> voiceDetection;

    void LinkEasyEase(){
       
       eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::fAnger), MeteorFace::fAnger, 60, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::fSadness), MeteorFace::fSadness, 60, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::fSurprised), MeteorFace::fSurprised, 60, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::fDoubt), MeteorFace::fDoubt, 60, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::fFrown), MeteorFace::fFrown, 60, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::fLookUp), MeteorFace::fLookUp, 60, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::fLookDown), MeteorFace::fLookDown, 60, 0.0f, 1.0f);

        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::vrc_v_ee), MeteorFace::vrc_v_ee, 2, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::vrc_v_ih), MeteorFace::vrc_v_ih, 2, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::vrc_v_dd), MeteorFace::vrc_v_dd, 2, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::vrc_v_rr), MeteorFace::vrc_v_rr, 2, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::vrc_v_ch), MeteorFace::vrc_v_ch, 2, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::vrc_v_aa), MeteorFace::vrc_v_aa, 2, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::vrc_v_oh), MeteorFace::vrc_v_oh, 2, 0.0f, 1.0f);
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::vrc_v_ss), MeteorFace::vrc_v_ss, 2, 0.0f, 1.0f);
        
        
        eEAface.AddParameter(face.GetMorphWeightReference(MeteorFace::fHideBlush), MeteorFace::fHideBlush, 30, 1.0f, 0.0f);
        eEAblush.AddParameter(blush.GetMorphWeightReference(MeteorBlush::blDefault), MeteorBlush::blDefault, 30, 1.0f, 0.0f);
        eEAblush.AddParameter(blush.GetMorphWeightReference(MeteorBlush::blMoveBlush), MeteorBlush::blMoveBlush, 30, 1.0f, 0.0f);

         eEAeye.AddParameter(eye.GetMorphWeightReference(MeteorEye::eClosed), MeteorEye::eClosed, 60, 0.0f, 1.0f);

       eEAbrow.AddParameter(brow.GetMorphWeightReference(MeteorBrow::bAngry), MeteorBrow::bAngry, 60, 0.0f, 1.0f);
       eEAbrow.AddParameter(brow.GetMorphWeightReference(MeteorBrow::bSurprise), MeteorBrow::bSurprise, 60, 0.0f, 1.0f);
       eEAbrow.AddParameter(brow.GetMorphWeightReference(MeteorBrow::bSad), MeteorBrow::bSad, 60, 0.0f, 1.0f);
        //eEAblush.AddParameter(blush.GetMorphWeightReference(MeteorBlush::MoveBlush), MeteorBlush::MoveBlush, 30, 1.0f, 0.0f);


        //eEAblush.AddParameter(blush.GetMorphWeightReference(MeteorBlush::MoveBlush), MeteorBlush::MoveBlush, 30, 1.0f, 0.0f);




        eEAface.AddParameter(&rainbowFaceMix, rainbowFaceIndex, 50, 0.0f, 1.0f);
        eEAface.AddParameter(&angryFaceMix, angryFaceIndex, 40, 0.0f, 1.0f);

        eEAeye.AddParameter(&rainbowFaceMix, rainbowFaceIndex, 50, 0.0f, 1.0f);
        eEAeye.AddParameter(&angryFaceMix, angryFaceIndex, 40, 0.0f, 1.0f);

        eEAbrow.AddParameter(&rainbowFaceMix, rainbowFaceIndex, 50, 0.0f, 1.0f);
        eEAbrow.AddParameter(&angryFaceMix, angryFaceIndex, 40, 0.0f, 1.0f);
 //blush
        eEAblush.AddParameter(&rainbowFaceMix, rainbowFaceIndex, 50, 0.0f, 1.0f);
        eEAblush.AddParameter(&angryFaceMix, angryFaceIndex, 40, 0.0f, 1.0f);
        
    }

/** links the blink morph to the blink frame track */
    void LinkParameters(){
        blink.AddParameter(eye.GetMorphWeightReference(MeteorEye::eBlink));
        //blink.AddParameter(brow.GetMorphWeightReference(MeteorBrow::blink));
    }

/** sets the interpolation method to either linear or cosine */
    void ChangeInterpolationMethods(){
        
        eEAblush.SetInterpolationMethod(MeteorBlush::blMoveBlush, EasyEaseInterpolation::Cosine);
        eEAface.SetInterpolationMethod(MeteorFace::fSadness, EasyEaseInterpolation::Cosine);
        
        eEAface.SetInterpolationMethod(rainbowFaceIndex, EasyEaseInterpolation::Cosine);
        eEAface.SetInterpolationMethod(angryFaceIndex, EasyEaseInterpolation::Cosine);

        eEAeye.SetInterpolationMethod(rainbowFaceIndex, EasyEaseInterpolation::Cosine);
        eEAeye.SetInterpolationMethod(angryFaceIndex, EasyEaseInterpolation::Cosine);
        eEAbrow.SetInterpolationMethod(rainbowFaceIndex, EasyEaseInterpolation::Cosine);
        eEAbrow.SetInterpolationMethod(angryFaceIndex, EasyEaseInterpolation::Cosine);
        eEAblush.SetInterpolationMethod(rainbowFaceIndex, EasyEaseInterpolation::Cosine);
        eEAblush.SetInterpolationMethod(angryFaceIndex, EasyEaseInterpolation::Cosine);






       
        eEAface.SetInterpolationMethod(MeteorFace::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEAface.SetInterpolationMethod(MeteorFace::vrc_v_ih, EasyEaseInterpolation::Linear);
        eEAface.SetInterpolationMethod(MeteorFace::vrc_v_dd, EasyEaseInterpolation::Linear);
        eEAface.SetInterpolationMethod(MeteorFace::vrc_v_rr, EasyEaseInterpolation::Linear);
        eEAface.SetInterpolationMethod(MeteorFace::vrc_v_ch, EasyEaseInterpolation::Linear);
        eEAface.SetInterpolationMethod(MeteorFace::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEAface.SetInterpolationMethod(MeteorFace::vrc_v_oh, EasyEaseInterpolation::Linear);
        eEAface.SetInterpolationMethod(MeteorFace::vrc_v_ss, EasyEaseInterpolation::Linear);
        
    }

/*** combines all the materials into one */
    void SetMaterials(){
        //faceMaterial.AddMaterial(Material::Add, &gradientMat, 0.5f);
        
        faceMaterial.AddMaterial(Material::Overlay, &rainbowNoise, 0.000000005f);
        //faceMaterial.AddMaterial(Material::Add, &yellow, 0.05f); //originally 0.6
        faceMaterial.AddMaterial(Material::Add, &ltYellowMat, 1.0f);
        faceMaterial.AddMaterial(Material::Add, &yellowMat, 0.1f); //originally 0.6

        faceMaterial.AddMaterial(Material::Replace, &rainbowSpiral, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &redMaterial, 0.0f);

        
    }
    /*
    void AddBlinkKeyFrames() {
        blink.AddKeyFrame(0.0f, 0.0f);
        blink.AddKeyFrame(2.75f, 0.0f);
        blink.AddKeyFrame(3.0f, 1.0f);
        blink.AddKeyFrame(3.25f, 0.0f);
        blink.AddKeyFrame(9.75f, 0.0f);
        blink.AddKeyFrame(10.0f, 1.0f);
        blink.AddKeyFrame(10.25f, 0.0f);
        blink.AddKeyFrame(10.75f, 0.0f);
        blink.AddKeyFrame(11.0f, 1.0f);
        blink.AddKeyFrame(11.25f, 0.0f);
        blink.AddKeyFrame(15.0f, 0.0f);
    }
    */

public:

    MeteorFaceAnimation() {
        boop.Initialize(600);
        //SerialSync::Initialize();
        //Serial.print("boop init?");
      scene.AddObject(background.GetObject());
      
      scene.AddObject(eye.GetObject());  
      scene.AddObject(face.GetObject());
      scene.AddObject(brow.GetObject());
      scene.AddObject(blush.GetObject());
        
        

        LinkEasyEase();
       LinkParameters();
       //AddBlinkKeyFrames();

        ChangeInterpolationMethods();

        SetMaterials();

       eye.GetObject()->SetMaterial(&faceMaterial); 
       blush.GetObject()->SetMaterial(&pinkMat); 
       face.GetObject()->SetMaterial(&faceMaterial);
       brow.GetObject()->SetMaterial(&faceMaterial);
        background.GetObject()->SetMaterial(&sA);

       //Menu menuObj;
       Menu::Initialize(9,0, 1000);//faces, pin, holding time
         //Menu::SetBrightness(8);
        MicrophoneFourier::Initialize(A8, 8000, 50.0f, 82.5f);//8KHz sample rate, 50dB min, 120dB max (original)
        
        //boop.Initialize(200);

    //SerialSync transfer;
      
    
        //SerialSync::SetDead(false);
        //SerialSync::Send();

        
    }

uint8_t GetAccentBrightness(){
        return Menu::GetAccentBrightness();
    };

    uint8_t GetBrightness(){
        return Menu::GetBrightness();
    };

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void doHappyFace(){

     eye.GetObject()->SetMaterial(&faceMaterial);
     face.GetObject()->SetMaterial(&faceMaterial);
     brow.GetObject()->SetMaterial(&faceMaterial);
     
     eEAblush.AddParameterFrame(MeteorBlush::blMoveBlush, 1.0f);
     eEAblush.AddParameterFrame(MeteorBlush::blDefault, 0.0f);
     blush.GetObject()->SetMaterial(&pinkMat);

    }

    void doBlushingFace(){

     eye.GetObject()->SetMaterial(&faceMaterial);
     face.GetObject()->SetMaterial(&faceMaterial);
     brow.GetObject()->SetMaterial(&faceMaterial);

     eEAblush.AddParameterFrame(MeteorBlush::blMoveBlush, 0.0f);
     blush.GetObject()->SetMaterial(&pinkMat);

    }

    void doAngryFace(){
        
        eye.GetObject()->SetMaterial(&redMaterial); 
        face.GetObject()->SetMaterial(&redMaterial); 
        brow.GetObject()->SetMaterial(&redMaterial); 
        
        eEAface.AddParameterFrame(MeteorFace::fAnger, 1.0f);
        eEAbrow.AddParameterFrame(MeteorBrow::bAngry, 1.0f);
    }

    void doSadFace(){
      
        eye.GetObject()->SetMaterial(&blueMat);
        face.GetObject()->SetMaterial(&blueMat);
        brow.GetObject()->SetMaterial(&blueMat);

        eEAface.AddParameterFrame(MeteorFace::fSadness, 1.0f);
        eEAbrow.AddParameterFrame(MeteorBrow::bSad, 1.0f);
    }

    void doBoopFace(){
        
            eye.GetObject()->SetMaterial(&rainbowSpiral);
            face.GetObject()->SetMaterial(&rainbowSpiral);
            brow.GetObject()->SetMaterial(&rainbowSpiral);

        eEAface.AddParameterFrame(MeteorFace::fSurprised, 1.0f);
        eEAbrow.AddParameterFrame(MeteorBrow::bSurprise, 1.0f);
    }

    void doSurpriseFace(){
        
       
        eye.GetObject()->SetMaterial(&purpleMat);
        face.GetObject()->SetMaterial(&purpleMat);
        brow.GetObject()->SetMaterial(&purpleMat);

        eEAface.AddParameterFrame(MeteorFace::fSurprised, 1.0f);
        eEAbrow.AddParameterFrame(MeteorBrow::bSurprise, 1.0f);
    }
    
    void doSleepFace(){
        
        eye.GetObject()->SetMaterial(&dkBlueMat);
        brow.GetObject()->SetMaterial(&dkBlueMat);
        face.GetObject()->SetMaterial(&dkBlueMat);

      
        eEAface.AddParameterFrame(MeteorFace::fDoubt, 1.0f);
        eEAbrow.AddParameterFrame(MeteorBrow::bSad,0.8f);
        eEAeye.AddParameterFrame(MeteorEye::eClosed, 0.9f);
       
    }
    
    void Frown(){
       
    }

    void LookUp(){

    }

    void LookDown(){

    }

 void doSpectrumAnalyzerWithFace(){
        background.GetObject()->Enable();
        background.GetObject()->SetMaterial(&sA);
        face.GetObject()->Enable();
        eye.GetObject()->Enable();
        brow.GetObject()->Enable();
        
        eye.GetObject()->SetMaterial(&pinkMat);
        face.GetObject()->SetMaterial(&pinkMat);
        brow.GetObject()->SetMaterial(&pinkMat);
        
    }

    void doSpectrumAnalyzerNoFace(){
        face.GetObject()->Disable();
        eye.GetObject()->Disable();
        brow.GetObject()->Disable();
        blush.GetObject()->Disable();
        background.GetObject()->Enable();
        background.GetObject()->SetMaterial(&sA);
    }

   
    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return face.GetObject();
        return eye.GetObject();
        return brow.GetObject();
        return blush.GetObject();
        return background.GetObject();
        
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEAface.AddParameterFrame(MeteorFace::vrc_v_ss, MicrophoneFourier::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourier::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourier::GetFourierFiltered(), MicrophoneFourier::GetSampleRate());
        
                eEAface.AddParameterFrame(MeteorFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEAface.AddParameterFrame(MeteorFace::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.IH));
               eEAface.AddParameterFrame(MeteorFace::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.DD));
               eEAface.AddParameterFrame(MeteorFace::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
               eEAface.AddParameterFrame(MeteorFace::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                eEAface.AddParameterFrame(MeteorFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEAface.AddParameterFrame(MeteorFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
            }
            //voiceDetection.PrintVisemes();
        }
    }

    void Update(float ratio) override {

        face.Reset();
        face.GetObject()->Enable();
        

        eye.Reset();
        eye.GetObject()->Enable();

        blush.Reset();
        blush.GetObject()->Enable();

        brow.Reset();
        brow.GetObject()->Enable();

        background.GetObject()->Disable();

        bool isBooped = boop.isBooped();
        uint8_t mode = Menu::GetFaceState();

        //Menu::printMenu();
        menuObj.printCurrentMenu();

        //change by button press
       SerialSync::SetMode(mode);


        MicrophoneFourier::Update();
        sA.Update(MicrophoneFourier::GetFourierFiltered());
        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        sA.SetMirrorYState(true);
        sA.SetFlipYState(true);
        
        UpdateFFTVisemes();

        /** change face emotion based on button press */
        if (isBooped && mode != (SpectrumAnalyzerNoFace||SpectrumAnalyzerWithFace)){
            doBoopFace();
        } else {

            switch (mode) {

                case HappyFace:
                    doHappyFace();
                    break;
            
                case BlushFace:
                    doBlushingFace();
                    break;

                case SurpriseFace:
                    doSurpriseFace();
                    break;

                case BoopFace:
                    doBoopFace();
                    break;

                case SadFace:
                    doSadFace();
                    break;

                case AngryFace:
                    doAngryFace();
                    break;

                case SpectrumAnalyzerNoFace:
                    doSpectrumAnalyzerNoFace();
                    break;

                case SpectrumAnalyzerWithFace:
                    doSpectrumAnalyzerWithFace();
                    break;

                case SleepFace:
                    doSleepFace();
                    break;

                default:
                    doHappyFace();
                    break;
            }

        }

        
        UpdateKeyFrameTracks();

        face.SetMorphWeight(MeteorFace::fMoveEye, 1.0f);

        eEAface.Update();
        eEAeye.Update();
        eEAbrow.Update();
        eEAblush.Update();

        face.Update();
        eye.Update();
        brow.Update();
        blush.Update();
        
        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
    
        faceMaterial.SetOpacity(3, rainbowFaceMix);//set face to spiral
        faceMaterial.SetOpacity(4, angryFaceMix);//set face to angry
        float x = int(sinf(ratio * 3.14159f / 180.0f * 360.0f * 1.0f) * 2.0f) * 5;
        float y = int(cosf(ratio * 3.14159f / 180.0f * 360.0f * 1.5f) * 2.0f) * 5;

        /* face transforms */
        face.GetObject()->GetTransform()->SetPosition(Vector3D(125.0f/*fGenMatXMove.Update()*/,-15.1f/* -15.0f + fGenMatYMove.Update()*/, 600.0f));
        face.GetObject()->GetTransform()->SetScale(Vector3D(-1.0f, 0.625f, 0.7f));
        face.GetObject()->UpdateTransform();

        /* eye transforms */
        eye.GetObject()->GetTransform()->SetPosition(Vector3D(130.0f -5 /*+x*//*fGenMatXMove.Update()*/,0.1f-10/* -15.0f *//*+ y*//*fGenMatYMove.Update()*/, 600.0f));
        eye.GetObject()->GetTransform()->SetScale(Vector3D(-1.0f, 0.625f, 0.7f));
        eye.GetObject()->UpdateTransform();

        /* brow transforms */
        brow.GetObject()->GetTransform()->SetPosition(Vector3D(130.0f -40/*fGenMatXMove.Update()*/,0.1f -45 /* -15.0f *//*fGenMatYMove.Update()*/, 500.0f));
        brow.GetObject()->GetTransform()->SetScale(Vector3D(1.0f, 0.825f, 0.7f)); 
        brow.GetObject()->UpdateTransform();
        
        /* blush transforms */
        blush.GetObject()->GetTransform()->SetPosition(Vector3D(125.0f-45/*fGenMatXMove.Update()*/,-10.1f/* -15.0f + fGenMatYMove.Update()*/, 300.0f));
        blush.GetObject()->GetTransform()->SetScale(Vector3D(-0.85f, 0.60f, 0.7f));
        blush.GetObject()->UpdateTransform();

        /* background transforms */
        background.GetObject()->GetTransform()->SetPosition(Vector3D(0.0f/*fGenMatXMove.Update()*/,0.0f/* -15.0f*fGenMatYMove.Update()*/, 100.0f));
        background.GetObject()->UpdateTransform();

      
    }
};
