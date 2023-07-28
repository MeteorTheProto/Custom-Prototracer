#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Objects\Background.h"

#include "..\Morph\NukudeFlat.h"




#include "..\Render\Scene.h"
#include "..\Signals\FunctionGenerator.h"
#include "..\Menu\SingleButtonMenu.h"
#include "..\Sensors\APDS9960.h"

#include "..\Materials\Animated\SpectrumAnalyzer.h"
#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Animated\RainbowSpiral.h"

#include "..\Materials\CombineMaterial.h"

#include "AnimationTracks\BlinkTrack.h"
//#include "KeyFrameTrack.h"

#include "..\Signals\FFTVoiceDetection.h"
#include "..\Sensors\MicrophoneFourier_MAX9814.h"

//#include "..\Flash\ImageSequences\VaporWave.h"



class ProtogenKitFaceAnimation : public Animation<4> {
private:

    Background background;
    NukudeFace face;
    
    
    
   

    EasyEaseAnimator<22> eEA = EasyEaseAnimator<22>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);

    //Materials
    RainbowNoise rainbowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255,15,15));
    
    RGBColor gradientSpectrum[2] = {RGBColor(225, 225, 0), RGBColor(225, 225, 168)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, true);
    SimpleMaterial yellow = SimpleMaterial(RGBColor(200,200,0)); //200,200,50
    SimpleMaterial lightYellow = SimpleMaterial(RGBColor(255,200,50)); //255,200,50
    SimpleMaterial pink = SimpleMaterial(RGBColor(255,0,50));
    SimpleMaterial teal = SimpleMaterial(RGBColor(89, 255, 150)); 
    SimpleMaterial purple = SimpleMaterial(RGBColor(100, 0, 255));
    SimpleMaterial blue = SimpleMaterial(RGBColor(25,25,255));
    SimpleMaterial darkblue = SimpleMaterial(RGBColor(12,12,255));
    CombineMaterial<5> faceMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(250, 200), Vector2D(120, 100), true, true);
    //VaporWaveSequence gif = VaporWaveSequence(Vector2D(250, 200), Vector2D(120, 100), 30);
    //Animation controllers
    BlinkTrack<1> blink;
    //KeyFrameTrack blink = KeyFrameTrack( 0.0f, 1.0f, KeyFrameTrack::Cosine);
    //Animatio blink = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -1.0f, 1.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -0.5f, 0.5f, 2.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -0.5f, 0.5f, 3.7f);

   APDS9960 boop;
    float rainbowFaceMix = 0.0f;
    float angryFaceMix = 0.0f;
    uint8_t rainbowFaceIndex = 50;
    uint8_t angryFaceIndex = 40;

    FFTVoiceDetection<128> voiceDetection;

    void LinkEasyEase(){
        /*
        eEA.AddParameter(eye.GetMorphWeightReference(Meteoreye::a), Meteoreye::a, 60, 0.0f, 1.0f);
        eEA.AddParameter(eye.GetMorphWeightReference(Meteoreye::b),Meteoreye::b, 60, 0.0f, 1.0f);
        eEA.AddParameter(eye.GetMorphWeightReference(Meteoreye::c), Meteoreye::c, 60, 0.0f, 1.0f);
        */
       //eEA.AddParameter(eye.GetMorphWeightReference(Meteoreye::blink), Meteoreye::blink, 60, 0.0f, 1.0f);
       //eEA.AddParameter(eye.GetMorphWeightReference(Meteoreye::Default), Meteoreye::Default, 1, 1.0f, 0.0f);

       //eEA.AddParameter(brow.GetMorphWeightReference(MeteorBrow::blink), MeteorBrow::blink, 60, 0.0f, 1.0f);
       //eEA.AddParameter(brow.GetMorphWeightReference(MeteorBrow::Default), MeteorBrow::Default, 1, 1.0f, 0.0f);
       
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::Anger), NukudeFace::Anger, 60, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::Sadness), NukudeFace::Sadness, 60, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::Surprised), NukudeFace::Surprised, 60, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::Doubt), NukudeFace::Doubt, 60, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::Frown), NukudeFace::Frown, 60, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::LookUp), NukudeFace::LookUp, 60, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::LookDown), NukudeFace::LookDown, 60, 0.0f, 1.0f);

        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::vrc_v_ee), NukudeFace::vrc_v_ee, 2, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::vrc_v_ih), NukudeFace::vrc_v_ih, 2, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::vrc_v_dd), NukudeFace::vrc_v_dd, 2, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::vrc_v_rr), NukudeFace::vrc_v_rr, 2, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::vrc_v_ch), NukudeFace::vrc_v_ch, 2, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::vrc_v_aa), NukudeFace::vrc_v_aa, 2, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::vrc_v_oh), NukudeFace::vrc_v_oh, 2, 0.0f, 1.0f);
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::vrc_v_ss), NukudeFace::vrc_v_ss, 2, 0.0f, 1.0f);
        
        /*Vector2D visEE = Vector2D(292.0f, 2352.0f);
    Vector2D visAE = Vector2D(660.0f, 1720.0f);
    Vector2D visUH = Vector2D(440.0f, 1020.0f);
    Vector2D visAR = Vector2D(818.0f, 1182.0f);
    Vector2D visER = Vector2D(490.0f, 1350.0f);
    Vector2D visAH = Vector2D(520.0f, 1190.0f);
    Vector2D visOO = Vector2D(300.0f, 870.0f);
    Vector2D visIH = Vector2D(390.0f, 1990.0f);
    Vector2D visDD = Vector2D(500.0f, 700.0f);*/
        eEA.AddParameter(face.GetMorphWeightReference(NukudeFace::HideBlush), NukudeFace::HideBlush, 30, 1.0f, 0.0f);

         


        //eEA.AddParameter(blush.GetMorphWeightReference(MeteorBlush::MoveBlush), MeteorBlush::MoveBlush, 30, 1.0f, 0.0f);




        eEA.AddParameter(&rainbowFaceMix, rainbowFaceIndex, 50, 0.0f, 1.0f);
        eEA.AddParameter(&angryFaceMix, angryFaceIndex, 40, 0.0f, 1.0f);
        
    }

    void LinkParameters(){
        blink.AddParameter(face.GetMorphWeightReference(NukudeFace::Blink));
        //blink.AddParameter(brow.GetMorphWeightReference(MeteorBrow::blink));
    }

    void ChangeInterpolationMethods(){
        
        //eEA.SetInterpolationMethod(MeteorBlush::MoveBlush, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(NukudeFace::Sadness, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(rainbowFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(angryFaceIndex, EasyEaseInterpolation::Cosine);
       
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ih, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_dd, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_rr, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ch, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_oh, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ss, EasyEaseInterpolation::Linear);
        
    }

    void SetMaterials(){
        //faceMaterial.AddMaterial(Material::Add, &gradientMat, 0.5f);
        
        faceMaterial.AddMaterial(Material::Overlay, &rainbowNoise, 0.000000005f);
        //faceMaterial.AddMaterial(Material::Add, &yellow, 0.05f); //originally 0.6
        faceMaterial.AddMaterial(Material::Add, &lightYellow, 1.0f);
        faceMaterial.AddMaterial(Material::Add, &yellow, 0.1f); //originally 0.6

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
    ProtogenKitFaceAnimation() {
      scene.AddObject(background.GetObject());
      
      
      scene.AddObject(face.GetObject());
     
      //scene.AddObject(blush.GetObject());
        
        

        LinkEasyEase();
       LinkParameters();
       //AddBlinkKeyFrames();

        ChangeInterpolationMethods();

        SetMaterials();

       
       //blush.GetObject()->SetMaterial(&pink); 
       face.GetObject()->SetMaterial(&faceMaterial);
       
        background.GetObject()->SetMaterial(&sA);

        Menu::Initialize(7, 0, 1000);//7 is number of faces

        MicrophoneFourierIT::Initialize(A8, 8000, 50.0f, 82.5f);//8KHz sample rate, 50dB min, 120dB max (original)
        
        boop.Initialize(600);

        
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

    void Default(){
        
        //eEA.AddParameterFrame(Meteoreye::blink, 1.0f);
     
     face.GetObject()->SetMaterial(&faceMaterial);
   
     
     
    }

    void Blushing(){
    
     face.GetObject()->SetMaterial(&faceMaterial);
     

     
    }

    void Angry(){
        
         
        face.GetObject()->SetMaterial(&redMaterial); 
        
        
        eEA.AddParameterFrame(NukudeFace::Anger, 1.0f);
      
    }

    void Sad(){
        
        //eEA.AddParameterFrame(MeteorBrow::Default, 1.0f);
        //eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
        
        face.GetObject()->SetMaterial(&blue);
        

        eEA.AddParameterFrame(NukudeFace::Sadness, 1.0f);
       
    }

    void BoopFace(){
        //eEA.AddParameterFrame(MeteorBlush::MoveBlush, 0.0f);
        //background.GetObject()->Enable();
        
        eEA.AddParameterFrame(NukudeFace::HideBlush, 0.0f);
        //blush.GetObject()->Enable();
         
            face.GetObject()->SetMaterial(&faceMaterial);
          

        eEA.AddParameterFrame(angryFaceIndex, 0.7f);
        eEA.AddParameterFrame(NukudeFace::Surprised, 1.0f);
        
    }

    void Surprised(){
        
        //eEA.AddParameterFrame(NukudeFace::HideBlush, 0.0f);
        //eEA.AddParameterFrame(rainbowFaceIndex, 0.7f);
        
        face.GetObject()->SetMaterial(&purple);
        

        eEA.AddParameterFrame(NukudeFace::Surprised, 1.0f);
        
    }
    
    void Sleepy(){
        
        
        face.GetObject()->SetMaterial(&darkblue);

        //blink.Pause();
        eEA.AddParameterFrame(NukudeFace::Doubt, 1.0f);
        
        //eEA.AddParameterFrame(Meteoreye::Closed, 0.9f);
        //background.GetObject()->Enable();
        //background.GetObject()->SetMaterial(&gif);
        //gif.Update();
    }
    
    void Frown(){
        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
      

    }

    void LookUp(){
        eEA.AddParameterFrame(NukudeFace::LookUp, 1.0f);
    }

    void LookDown(){
        eEA.AddParameterFrame(NukudeFace::LookDown, 1.0f);
    }

 void SpectrumAnalyzerWithFace(){
        background.GetObject()->Enable();
        background.GetObject()->SetMaterial(&sA);
        face.GetObject()->Enable();
        
        //background.GetObject()->GetTransform()->SetPosition(Vector3D(0.0f/*fGenMatXMove.Update()*/,0.0f/* -15.0f /*fGenMatYMove.Update()*/, 100.0f));
        //background.GetObject()->UpdateTransform();
        
        face.GetObject()->SetMaterial(&rainbowSpiral);
       
        
    }

    void SpectrumAnalyzerNoFace(){
        face.GetObject()->Disable();
        
        background.GetObject()->Enable();
        background.GetObject()->SetMaterial(&sA);
    }

   
    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return face.GetObject();
        
        return background.GetObject();
        
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEA.AddParameterFrame(NukudeFace::vrc_v_ss, MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
        
                eEA.AddParameterFrame(NukudeFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(NukudeFace::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.IH));
               eEA.AddParameterFrame(NukudeFace::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.DD));
               eEA.AddParameterFrame(NukudeFace::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
               eEA.AddParameterFrame(NukudeFace::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(NukudeFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(NukudeFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
            }
            voiceDetection.PrintVisemes();
        }
    }

    void Update(float ratio) override {

        //blink.Play();

        face.Reset();
        face.GetObject()->Enable();
        

        

       

        

        background.GetObject()->Disable();

        bool isBooped = Menu::UseBoopSensor() ? boop.isBooped() : 0;
        uint8_t mode = Menu::GetFaceState();//change by button press

        MicrophoneFourierIT::Update();
        sA.Update(MicrophoneFourierIT::GetFourierFiltered());
        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        sA.SetMirrorYState(true);
        sA.SetFlipYState(true);
        
        UpdateFFTVisemes();

        if (isBooped && mode != 6){
            BoopFace();
        }
        else {
            if (mode == 0) Default();
            else if (mode == 1) Angry();
            else if (mode == 2) Surprised();
            else if (mode ==3) Sad();
            else if (mode ==4) BoopFace();
            else if (mode ==5) SpectrumAnalyzerWithFace();
            else if (mode ==6) SpectrumAnalyzerNoFace();
            else Sleepy();

        }

        
    UpdateKeyFrameTracks();

        

        //face.SetMorphWeight(NukudeFace::BiggerNose, 1.0f);
        face.SetMorphWeight(NukudeFace::MoveEye, 1.0f);

        eEA.Update();
        face.Update();
        
        
        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
    
        faceMaterial.SetOpacity(2, rainbowFaceMix);//set face to spiral
        faceMaterial.SetOpacity(3, angryFaceMix);//set face to angry
        float x = int(sinf(ratio * 3.14159f / 180.0f * 360.0f * 1.0f) * 2.0f) * 5;
        float y = int(cosf(ratio * 3.14159f / 180.0f * 360.0f * 1.5f) * 2.0f) * 5;

        //face.GetObject()->GetTransform()->SetPosition(Vector3D(130.0f + x, -15.0f + y, 600.0f));

        face.GetObject()->GetTransform()->SetPosition(Vector3D(125.0f/*fGenMatXMove.Update()*/,-15.1f/* -15.0f + fGenMatYMove.Update()*/, 600.0f));
        face.GetObject()->GetTransform()->SetScale(Vector3D(-1.0f, 0.625f, 0.7f));

        face.GetObject()->UpdateTransform();

       


        background.GetObject()->GetTransform()->SetPosition(Vector3D(0.0f/*fGenMatXMove.Update()*/,0.0f/* -15.0f*fGenMatYMove.Update()*/, 100.0f));
        background.GetObject()->UpdateTransform();

      
    }
};
