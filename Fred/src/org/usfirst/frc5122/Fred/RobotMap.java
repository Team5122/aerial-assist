// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// Java from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
package org.usfirst.frc5122.Fred;
    
import com.team254.lib.CheesyVisionServer;
import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;
import java.util.Vector;
/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
public class RobotMap {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    public static SpeedController drivetrainRR;
    public static SpeedController drivetrainLF;
    public static SpeedController drivetrainLR;
    public static SpeedController drivetrainRF;
    public static RobotDrive drivetrainRobotDrive4;
    public static SpeedController throwerIndexer;
    public static DigitalInput throwerLimitSwitch;
    public static SpeedController armRoller;
    public static Solenoid armDeploy;
    public static Compressor pneumaticCompressor;
    public static Ultrasonic distanceUltrasonic;
    public static DigitalOutput decorationsTeleopSignal;
    public static DigitalInput iRIRCode;
    public static DoubleSolenoid throwupPopBall;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	public static CheesyVisionServer CheesyServer;
	public static final int cheesylistenPort = 1180;
    public static void init() {
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
        drivetrainRR = new Victor(1, 2);
	LiveWindow.addActuator("Drivetrain", "RR", (Victor) drivetrainRR);
        
        drivetrainLF = new Victor(1, 3);
	LiveWindow.addActuator("Drivetrain", "LF", (Victor) drivetrainLF);
        
        drivetrainLR = new Victor(1, 4);
	LiveWindow.addActuator("Drivetrain", "LR", (Victor) drivetrainLR);
        
        drivetrainRF = new Victor(1, 1);
	LiveWindow.addActuator("Drivetrain", "RF", (Victor) drivetrainRF);
        
        drivetrainRobotDrive4 = new RobotDrive(drivetrainLF, drivetrainLR,
              drivetrainRF, drivetrainRR);
	
        drivetrainRobotDrive4.setSafetyEnabled(true);
        drivetrainRobotDrive4.setExpiration(0.5);
        drivetrainRobotDrive4.setSensitivity(0.5);
        drivetrainRobotDrive4.setMaxOutput(1.0);
        drivetrainRobotDrive4.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        drivetrainRobotDrive4.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        drivetrainRobotDrive4.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        drivetrainRobotDrive4.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
        throwerIndexer = new Victor(1, 5);
	LiveWindow.addActuator("Thrower", "Indexer", (Victor) throwerIndexer);
        
        throwerLimitSwitch = new DigitalInput(1, 1);
	LiveWindow.addSensor("Thrower", "Limit Switch", throwerLimitSwitch);
        
        armRoller = new Victor(1, 6);
	LiveWindow.addActuator("Arm", "Roller", (Victor) armRoller);
        
        armDeploy = new Solenoid(1, 1);
	LiveWindow.addActuator("Arm", "Deploy", armDeploy);
        
        pneumaticCompressor = new Compressor(1, 2, 1, 1);
	
        
        distanceUltrasonic = new Ultrasonic(1, 3, 1, 4);
	LiveWindow.addSensor("Distance", "Ultrasonic", distanceUltrasonic);
        
        decorationsTeleopSignal = new DigitalOutput(1, 5);
	
        
        iRIRCode = new DigitalInput(1, 6);
	LiveWindow.addSensor("IR", "IR Code", iRIRCode);
        
        throwupPopBall = new DoubleSolenoid(1, 5, 6);      
	
        
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	CheesyServer = CheesyVisionServer.getInstance();
    
    }
}
