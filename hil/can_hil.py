# Copyright 2023 OroraTech GmbH
# Licensed under the terms and conditions of the Apache 2.0 license.
#

import sys
import time
import struct
import can
import RPi.GPIO as GPIO

c_aluminium = 900  # J / kg * K
absorb_aluminium = 0.2
h_sun = 64E6  # power density sun, W / m^2
stefanboltzmann = 1.3806505E-8
r_sun = 695E6  # m, radius sun

distance_sun = 150E9  # m, average constant distance
A_sat = 0.32  # m^2
a_to_sun = 0.3  # part of satellite in direct sunlight
m_sat = 8  # kg
step_size = 1  # s

emissivity = 0.7  # random aluminium value


class Sat:
    temp = -4.0

    p_heater = 15
    p_payload = 3
    p_sat = 10
    specific_heat = c_aluminium
    sun_absorbtion = absorb_aluminium

    in_sun = True
    payload_enabled = False
    heater_enabled = False

    def step(self):
        p_rad = stefanboltzmann * A_sat * \
            ((self.temp + 273.15) ** 4) * emissivity

        # print("p_rad", p_rad)

        p_sun = 0
        if self.in_sun:
            p_sun = ((r_sun ** 2) * (h_sun) / (distance_sun ** 2)) * \
                (A_sat * a_to_sun) * self.sun_absorbtion

        # print("p_sun", p_sun)
        p_payload = 0
        if self.payload_enabled:
            p_payload = self.p_payload

        p_heater = 0
        if self.heater_enabled:
            p_heater = self.p_heater

        p_total = p_heater + p_payload + self.p_sat + p_sun - p_rad

        delta_t = (step_size * p_total) / (self.specific_heat * m_sat)
        self.temp += delta_t


sat = Sat()
sat.in_sun = False
i = 0

GPIO.setmode(GPIO.BCM)
GPIO.setup(20, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)

print("time,payload,heater,temperature")

with can.interface.Bus(channel="can0", interface="socketcan") as bus:
    while True:
        sat.payload_enabled = GPIO.input(21)
        sat.heater_enabled = GPIO.input(20)

        sat.step()
        i = i + step_size

        print(str(i)+","+str(sat.payload_enabled)+"," +
              str(sat.heater_enabled)+","+str(sat.temp))

        temp_bin = struct.pack('<f', sat.temp)
        temp_bin = temp_bin + temp_bin
        msg = can.Message(arbitration_id=0xF, data=temp_bin,
                          is_extended_id=True)
        bus.send(msg)

        sys.stdout.flush()
        time.sleep(1)
