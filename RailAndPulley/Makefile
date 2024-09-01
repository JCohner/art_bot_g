
compile:
	@arduino-cli compile --output-dir bin --fqbn arduino:avr:uno -v --build-path build .

deploy:
	# can parse `arduino-cli board list` with awk if needed 
	arduino-cli upload --input-file bin/RailAndPulley.ino.with_bootloader.bin --fqbn arduino:avr:uno -p /dev/ttyACM0 --verbose