import os

speed = 50
velr = 70
vell = 70

while(True):
	cmd = raw_input()

	if (cmd == 'list'):
		os.system('for f in /sys/class/tacho-motor/*; do echo -n "$f: "; cat $f/port_name; done')
	
	if(cmd == 'quit'):
		exit()
		
	if(cmd == 'poweroff'):
		os.system("poweroff")
		
	if(cmd == 'seecommands'):
		os.system("cat /sys/class/tacho-motor/motor0/commands")	
		os.system("cat /sys/class/tacho-motor/motor1/commands")	
				
	if(cmd == 'reset'):
		os.system("echo reset > /sys/class/tacho-motor/motor0/command")
		os.system("echo reset > /sys/class/tacho-motor/motor1/command")
			
	if(cmd == 'run'):
		os.system("echo "+str(speed)+" > /sys/class/tacho-motor/motor0/duty_cycle_sp")
		os.system("echo "+str(speed)+" > /sys/class/tacho-motor/motor1/duty_cycle_sp")
		os.system("echo run-forever > /sys/class/tacho-motor/motor0/command");
		os.system("echo run-forever > /sys/class/tacho-motor/motor1/command");
		
	if(cmd == 'back'):
		os.system("echo -"+str(speed)+"  > /sys/class/tacho-motor/motor0/duty_cycle_sp")
		os.system("echo -"+str(speed)+" > /sys/class/tacho-motor/motor1/duty_cycle_sp")
		os.system("echo run-forever > /sys/class/tacho-motor/motor0/command");
		os.system("echo run-forever > /sys/class/tacho-motor/motor1/command");
		
	if(cmd == 'right'):
		os.system("echo -"+str(speed)+" > /sys/class/tacho-motor/motor0/duty_cycle_sp")
		os.system("echo "+str(speed)+" > /sys/class/tacho-motor/motor1/duty_cycle_sp")
		os.system("echo run-forever > /sys/class/tacho-motor/motor0/command");
		os.system("echo run-forever > /sys/class/tacho-motor/motor1/command");
	
	if(cmd == 'left'):
		os.system("echo "+str(speed)+" > /sys/class/tacho-motor/motor0/duty_cycle_sp")
		os.system("echo -"+str(speed)+" > /sys/class/tacho-motor/motor1/duty_cycle_sp")
		os.system("echo run-forever > /sys/class/tacho-motor/motor0/command");
		os.system("echo run-forever > /sys/class/tacho-motor/motor1/command");

	if(cmd == 'setvel'):
		speed = input()
		os.system(" echo "+str(speed)+" > /sys/class/tacho-motor/motor0/duty_cycle_sp")
		os.system(" echo "+str(speed)+" > /sys/class/tacho-motor/motor1/duty_cycle_sp")
		
	if(cmd == 'velr'):
		velr = input()
		os.system(" echo "+str(velr)+" > /sys/class/tacho-motor/motor0/duty_cycle_sp")

	if(cmd == 'vell'):
		vell = input()
		os.system(" echo "+str(vell)+" > /sys/class/tacho-motor/motor1/duty_cycle_sp")
		
	if(cmd == 'rundirect'):
		os.system(" echo run-direct > /sys/class/tacho-motor/motor0/command")
		os.system(" echo run-direct > /sys/class/tacho-motor/motor1/command")
	
	if(cmd == 'x'):
		os.system("echo stop > /sys/class/tacho-motor/motor0/command")
		os.system("echo stop > /sys/class/tacho-motor/motor1/command")
