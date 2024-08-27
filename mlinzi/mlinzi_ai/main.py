# import cv2
# import numpy as np

# # Load YOLO
# net = cv2.dnn.readNet('yolov3.weights', 'yolov3.cfg')
# layer_names = net.getLayerNames()
# output_layers = [layer_names[i - 1] for i in net.getUnconnectedOutLayers().flatten()]

# # Load COCO names
# with open('coco.names', 'r') as f:
#     classes = [line.strip() for line in f.readlines()]

# # Initialize webcam
# cap = cv2.VideoCapture(0)

# # Initialize tracker
# tracker = cv2.TrackerCSRT_create()  # Change tracker here if needed

# tracking = False
# bbox = None
# confidence_threshold = 0.3  # Adjust as needed
# nms_threshold = 0.2

# while True:
#     ret, frame = cap.read()
#     if not ret:
#         break

#     height, width, channels = frame.shape

#     if not tracking:
#         # Detect objects
#         blob = cv2.dnn.blobFromImage(frame, 0.00392, (416, 416), (0, 0, 0), True, crop=False)
#         net.setInput(blob)
#         outs = net.forward(output_layers)

#         class_ids = []
#         confidences = []
#         boxes = []

#         for out in outs:
#             for detection in out:
#                 scores = detection[5:]
#                 class_id = np.argmax(scores)
#                 confidence = scores[class_id]
#                 if confidence > confidence_threshold and (class_id == 0 or class_id == 16 or class_id == 17):  # Adjust class ids as needed
#                     center_x = int(detection[0] * width)
#                     center_y = int(detection[1] * height)
#                     w = int(detection[2] * width)
#                     h = int(detection[3] * height)
#                     x = int(center_x - w / 2)
#                     y = int(center_y - h / 2)

#                     boxes.append([x, y, w, h])
#                     confidences.append(float(confidence))
#                     class_ids.append(class_id)

#         indexes = cv2.dnn.NMSBoxes(boxes, confidences, confidence_threshold, nms_threshold)

#         if len(indexes) > 0:
#             for i in indexes.flatten():
#                 x, y, w, h = boxes[i]
#                 label = f"{classes[class_ids[i]]}: {confidences[i]:.2f}"
#                 cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
#                 cv2.putText(frame, label, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
#                 bbox = (x, y, w, h)
#                 tracking = True
#                 tracker.init(frame, bbox)
#         else:
#             tracking = False

#     else:
#         # Track object
#         success, bbox = tracker.update(frame)
#         if success:
#             p1 = (int(bbox[0]), int(bbox[1]))
#             p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
#             cv2.rectangle(frame, p1, p2, (0, 255, 0), 2)
#             cv2.putText(frame, 'Tracking', (p1[0], p1[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
#         else:
#             tracking = False

#     cv2.imshow('Webcam - Object Detection and Tracking', frame)

#     if cv2.waitKey(1) & 0xFF == ord('q'):
#         break

# cap.release()
# cv2.destroyAllWindows()


from ultralytics import YOLO
import cv2

# Load the YOLOv8 model
model = YOLO("yolov8n.pt")

# Initialize webcam
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Run detection
    results = model(frame, classes=[0, 15, 16])  # 0: person, 15: dog, 16: cat

    # Render results on the frame
    annotated_frame = results[0].plot()

    # Display the output
    cv2.imshow("YOLOv8 - Object Detection", annotated_frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
