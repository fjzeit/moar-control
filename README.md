# Moar Control

**Work in Progress**

An Arduino-based MIDI controller designed specifically for the IK Multimedia ToneX pedal, providing tactile control over tone shaping and effects parameters.

## Overview

This project implements a custom MIDI controller using an Arduino Uno to interface with the IK Multimedia ToneX pedal. The controller provides hands-on control over the pedal's various tone models and effects processing capabilities through intuitive physical controls.

## Features

- **Multi-Parameter Control**: Three main potentiometers ("Meat", "Gravy", "Veg") for primary tone adjustment
- **Fine-Tuning**: Five rotary encoders for precise parameter control
- **Mode Selection**: Switch between different effect categories (Amp, Alt, Reverb, Compressor, Gate)
- **Visual Feedback**: LED bank for status indication
- **MIDI Integration**: Sends MIDI Control Change messages directly to ToneX pedal

## Hardware

- Arduino Uno
- 4 potentiometers (including mode selection)
- 5 rotary encoders
- 2 push buttons
- LED strip/bank for visual feedback
- MIDI output to ToneX pedal

## ToneX Effects Controlled

- **Reverb**: Time, pre-delay, color, mix, and type controls
- **Compressor**: Threshold, makeup gain, attack, and pre/post patch routing
- **Noise Gate**: Threshold, release, and depth parameters  
- **EQ**: Presence, depth, mix, and 3-band parametric controls with frequency adjustment
- **Amp Modeling**: Tone model mix and various amp parameters

## Getting Started

This project uses PlatformIO for Arduino development. Load the project in PlatformIO and upload to an Arduino Uno board.

Connect the MIDI output from the Arduino to the MIDI input of your IK Multimedia ToneX pedal to begin controlling tone parameters in real-time.