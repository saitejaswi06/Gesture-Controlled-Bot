import cv2
import mediapipe as mp
import socket
from model import KeyPointClassifier
import landmark_utils as u

# Initialize MediaPipe and the classifier
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_hands = mp.solutions.hands

kpclf = KeyPointClassifier()

# Gesture mappings
gestures = {
    0: "Open Hand",
    1: "Thumb up",
    2: "OK",
    3: "Peace",
    4: "No Hand Detected"
}

# Socket setup to send data to ESP over Wi-Fi
ESP_IP = "192.168.157.115"  # Replace with your ESP's IP address
ESP_PORT = 80               # Replace with your ESP's listening port

# Create and connect the socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((ESP_IP, ESP_PORT))
print(f"Connected to ESP at {ESP_IP}:{ESP_PORT}")

# For webcam input
cap = cv2.VideoCapture(0)
with mp_hands.Hands(
        model_complexity=0,
        min_detection_confidence=0.5,
        min_tracking_confidence=0.5) as hands:
    try:
        while cap.isOpened():
            success, image = cap.read()
            if not success:
                print("Ignoring empty camera frame.")
                continue

            # To improve performance, mark the image as not writable
            image.flags.writeable = False
            image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
            results = hands.process(image)

            # Draw the hand annotations on the image
            image.flags.writeable = True
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            gesture_index = 4  # Default to "No Hand Detected"

            if results.multi_hand_landmarks:
                for hand_landmarks in results.multi_hand_landmarks:
                    landmark_list = u.calc_landmark_list(image, hand_landmarks)
                    keypoints = u.pre_process_landmark(landmark_list)
                    gesture_index = kpclf(keypoints)

                    mp_drawing.draw_landmarks(
                        image,
                        hand_landmarks,
                        mp_hands.HAND_CONNECTIONS,
                        mp_drawing_styles.get_default_hand_landmarks_style(),
                        mp_drawing_styles.get_default_hand_connections_style())

            # Print the gesture index in the terminal
            print(f"Detected Gesture Index: {gesture_index}")

            # Send the gesture index to the ESP
            gesture_data = (str(gesture_index) + "\n").encode()
            client_socket.sendall(gesture_data)

            # Flip the image horizontally for a selfie-view display
            final = cv2.flip(image, 1)
            cv2.putText(final, gestures[gesture_index],
                        (10, 30), cv2.FONT_HERSHEY_DUPLEX, 1, 255)
            cv2.imshow('MediaPipe Hands', final)

            if cv2.waitKey(5) & 0xFF == 27:
                break

    except KeyboardInterrupt:
        print("\nInterrupted by user.")

    finally:
        cap.release()
        client_socket.close()
        cv2.destroyAllWindows()
        print("Connection closed.")
