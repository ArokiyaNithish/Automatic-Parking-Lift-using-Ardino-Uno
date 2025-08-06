if (digitalRead(IRSensor) == HIGH):
    Serial.println("The ir sensor identify the car for parking slot")# print for conform the car is to parking in the lift
    delay(1000)# 1 seconds for next process
    
    if(digitalRead(IRSensor) == HIGH):
        if (startTime == 0): #if this is the first detection
            startTime = millis() # record the start time
        else if:
            (millis() - startTime >= detectionTime)# if the object has been detected for 2 seconds
            Serial.println("Car is detected!")#Print message to serial monitor
            digitalWrite(motorDirectionPin1, HIGH)#Set motor direction (adjust according to your motor driver)
            digitalWrite(motorDirectionPin2, LOW)
            analogWrite(motorDirectionPin1, motorSpeed)
            digitalWrite(motorEnablePin, LOW) #Enable motor (adjust HIGH/LOW based on motor driver configuration)
            delay(2000)# 2 seconds (delay before next detection)
    
# Stop the motor (both directions) using ultrasonic senor by the distance of 172cm   
            if (distance_cm < DISTANCE_THRESHOLD1):
                digitalWrite(motorDirectionPin1, LOW)
                digitalWrite(motorDirectionPin2, LOW)
                digitalWrite(motorEnablePin, LOW)
                Serial.print("first floor!")# Print the value to Serial Monitor
                delay(200)# Delay for stability
    
      
                if (distance_cm2 > DISTANCE_THRESHOLD2):
                    servo.write(0)# Rotate servo motor to 0 degrees
                    Serial.print("There is Free Space!")
                    delay(5)# Wait for a moment before the next measurement

                    #the convery motor to run the dection  of ultrasonic sensor
      
                    digitalWrite(motorForwardPin, HIGH)
                    delay(1200); // 2 minutes in milliseconds
                    digitalWrite(motorForwardPin, LOW) # to Stop
                    delay(1000)# Pause for 1 second

                    #Move backward for 2 minutes
                    digitalWrite(motorBackwardPin, HIGH);
                    delay(120000); // 2 minutes in milliseconds
                    digitalWrite(motorBackwardPin, LOW);// Stop
     
  
                else if (distance_cm2 < DISTANCE_THRESHOLD2)
                    servo.write(90); // Rotate servo motor to 0 degrees
                    delay(5); // Wait for a moment before the next measurement
  
     

else 
  
        Serial.println(" "); // Print message to serial monitor
        // Disable motor
        digitalWrite(motorEnablePin, LOW);
  

   
    