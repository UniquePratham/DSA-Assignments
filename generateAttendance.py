import random
import csv
from faker import Faker

# Initialize the Faker object for generating random names
fake = Faker()

# Create random data for 20 students
num_students = 20
num_dates = 31  # You can change the number of dates as needed

# Generate random student data
student_data = []
for i in range(1, num_students + 1):
    name = fake.name()
    roll_number = f"Roll{i:03}"
    attendance_data = [random.randint(0, 1) for _ in range(
        num_dates)]  # 0 for absent, 1 for present
    student_data.append([roll_number, name] + attendance_data)

# Write the data to the "attendance.txt" file
with open("attendance.txt", "w", newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["RollNumber", "Name"] +
                    [f"Date{i+1}" for i in range(num_dates)])
    writer.writerows(student_data)

print("attendance.txt has been created with random data.")
