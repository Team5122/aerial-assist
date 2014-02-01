/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package edu.wpi.first.wpilibj.templates;


import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.RobotDrive;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class RobotTemplate extends SimpleRobot {
    Joystick js;
    Victor jagR1;
    Victor jagR2;
    Victor jagL1;
    Victor jagL2;
    Compressor pump;
    RobotDrive drivetrain;

    public RobotTemplate() {
        this.js = new Joystick(1);
        this.jagR1 = new Victor(3);
        this.jagR2 = new Victor(4);
        this.jagL1 = new Victor(1);
        this.jagL2 = new Victor(2);
        this.pump = new Compressor(1,1); //Note White-Black
        this.drivetrain = new RobotDrive(jagL1, jagL2, jagR1, jagR2);
        System.out.println("Constructor");
        
    }
    public void robotInit()
    {
        System.out.println("Init.");
        pump.start();
        
    }
    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        while ((isEnabled() && isOperatorControl()))
            {
                drivetrain.arcadeDrive(js, false);
                if (js.getRawButton(3))
                {
                    
                }
            }
    }
    
    /**
     * This function is called once each time the robot enters test mode.
     */
    public void test() {
        System.out.println("Test");
        while(true)
        {
            System.out.println("PS: "+pump.getPressureSwitchValue());
        }
    }
}
