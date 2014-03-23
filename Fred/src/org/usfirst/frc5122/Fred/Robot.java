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
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.Scheduler;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;
import org.usfirst.frc5122.Fred.commands.*;
import org.usfirst.frc5122.Fred.subsystems.*;
/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Robot extends IterativeRobot {
    Command autonomousCommand;
    public static OI oi;
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    public static Drivetrain drivetrain;
    public static Thrower thrower;
    public static Arm arm;
    public static Pneumatic pneumatic;
    public static Distance distance;
    public static Decorations decorations;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit() {
	RobotMap.init();
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
        drivetrain = new Drivetrain();
        thrower = new Thrower();
        arm = new Arm();
        pneumatic = new Pneumatic();
        distance = new Distance();
        decorations = new Decorations();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
        // This MUST be here. If the OI creates Commands (which it very likely
        // will), constructing it during the construction of CommandBase (from
        // which commands extend), subsystems are not guaranteed to be
        // yet. Thus, their requires() statements may grab null pointers. Bad
        // news. Don't move it.
        oi = new OI();
	Robot.drivetrain.setSafetyEnabled(false);
        
        // instantiate the command used for the autonomous period
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
        autonomousCommand = new Auto();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
    }
    public void autonomousInit() {
        Robot.decorations.setAuto();
	Robot.drivetrain.setSafetyEnabled(false);
	autonomousCommand = new Auto();
        // schedule the autonomous command (example)
        Robot.drivetrain.setSafetyEnabled(false);
        if (autonomousCommand != null) autonomousCommand.start();
    }
    /**
     * This function is called periodically during autonomous
     */
    public void autonomousPeriodic() {
        Scheduler.getInstance().run();
    }
    public void teleopInit() {
        System.out.println("------- Teleop! -------");
        Robot.decorations.setTeleop();
		// This makes sure that the autonomous stops running when
        // teleop starts running. If you want the autonomous to 
        // continue until interrupted by another command, remove
        // this line or comment it out.
        if (autonomousCommand != null) autonomousCommand.cancel();
        Robot.drivetrain.setSafetyEnabled(true);
    }
    /**
     * This function is called periodically during operator control
     */
    public void teleopPeriodic() {
        Scheduler.getInstance().run();
    }
    /**
     * This function called periodically during test mode
     */
    public void testPeriodic() {
        LiveWindow.run();
    }
    public void disabledInit() {
        Robot.arm.isArmDown = false;
        Robot.arm.Up();
        if (autonomousCommand != null) autonomousCommand.cancel();
    }
}
