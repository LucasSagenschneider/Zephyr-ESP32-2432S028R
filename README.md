# Zephyr-ESP32-2432S028R

This project should serve as a starting point for the ESP32-2432S028R circuit board.
(also known as the cheap yellow display)
I plan to configure Zephyr for this board.

The setup will first follow the examples from Shawn.
I would also like to give a big thanks to him. he has built a great tutorial on Youtube.
https://github.com/ShawnHymel/introduction-to-zephyr

I use these commands most frequently:

start the docker image (in Windows)

1. start the docker desktop app
2. start a power shell and navigate to the repr
3. call this command

   ```
   docker run --rm -it -p 3333:3333 -p 2222:22 -p 8800:8800 -v "${PWD}\workspace:/workspace" -w /workspace env-zephyr-espressif
   ```

Build the Project (in Docker)

1. navigate to the sources (e.g. /workspace/apps/demo_app)
2. call this command

   ```
   west build -p always -b esp32_devkitc_wroom/esp32/procpu -- -DDTC_OVERLAY_FILE=boards/esp32_devkitc_wroom.overlay
   ```

Flashen Build to the board (Power shell in Windows)

1. activate the virtual invirement by calling this command
   ```
   .\venv\Scripts\activate
   ```
2. Flash the bin to the Board (change the COM port)
   ```
   python -m esptool --port "COM9" --chip auto --baud 921600 --before default_reset --after hard_reset write_flash -u --flash_size detect 0x1000 .\workspace\apps\demo_app\build\zephyr\zephyr.bin
   ```

3. Serial Terminal (optional)
   ```
   python -m serial.tools.miniterm "COM9" 115200
   ```
