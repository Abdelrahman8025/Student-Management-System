/*
 ============================================================================
 Name        : Final_C_Project
 Author      : Abdelraman Ahmed
 Version     :
 Copyright   : Your copyright notice
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to store student information.
typedef struct student
{
	int id;            // Student ID
	char name[50];     // Student name (up to 49 characters)
	int age;           // Student age
	float gpa;         // Student GPA
}student;



// Define a structure to represent a node in a linked list.
typedef struct node
{
	student data; 	   // Data stored in this node (student information)
	struct node *next; // Pointer to the next node in the list
}node;

node *head = NULL; // Initialize the head of the linked list to NULL


// Function to add a new student to the linked list
void addStudent(const struct student *const ptr)
{
	// Allocate memory for a new node
	node *newnode = (node*)malloc(sizeof(node));

	// Check if memory allocation was successful
	if (newnode == NULL)
	{
		// Print error message and return if allocation failed
		fprintf(stderr, "Memory allocation failed.\n");
		return;
	}
	else
	{
		// Initialize the new node with the given student data
		newnode -> data.id = ptr ->id;
		strncpy(newnode->data.name, ptr->name, sizeof(newnode->data.name) - 1);
		newnode->data.name[sizeof(newnode->data.name) - 1] = '\0'; // Ensure null-termination
		newnode -> data.age = ptr ->age;
		newnode -> data.gpa = ptr ->gpa;
		newnode -> next = NULL;
	}

	// Traverse the list to check if a student with the same ID already exists
	node *current = head;
	node *prev = NULL;
	while (current != NULL)
	{
		if (current->data.id == ptr->id)
		{
			// If a student with the same ID is found, print an error message and free the memory
			printf("This ID is already reserved.\n");
			free(newnode); // Free allocated memory for new node
			return;
		}
		prev = current;
		current = current->next;
	}

	// If head is NULL, this is the first node
	if (head == NULL) {
		head = newnode;
	} else {
		// Append new node at the end of the list
		prev->next = newnode;
	}

	// Confirm the addition of the student
	printf("Student with ID %d added successfully.\n", newnode->data.id);
}


// Function to display all students in the list
void displayStudents(void)
{
	if (head == NULL)
	{
		// If the list is empty, inform the user
		printf("The Student List is Empty.\n");
	}
	else
	{
		// Traverse the list and print each student's information
		node *current = head;
		while(current != NULL)
		{
			printf ("[ID : %d, Name : %s , Age : %d , GPA : %f]\n",current -> data.id , current -> data.name , current -> data.age , current -> data.gpa);
			current = current -> next;
		}
	}
}


// Function to search for a student by ID
void searchStudentByID(int id)
{
	if (head == NULL)
	{
		// If the list is empty, inform the user
		printf("The Student List is Empty.\n");
		return;
	}
	else
	{
		// Traverse the list to find the student with the given ID
		node *current = head;
		while (current != NULL)
		{
			// If found, print the student's details
			if(current -> data.id == id)
			{
				printf("Student Found :\n");
				printf ("ID : %d, Name : %s , Age : %d , GPA : %f\n",current -> data.id , current -> data.name , current -> data.age , current -> data.gpa);
				return; // Exit the function once the student is found
			}
			current = current -> next;
		}
	}
	// If the student wasn't found, print a message
	printf("Student with ID %d wasn't found.\n", id);
}


// Function to update the information of a student with a given ID
void updateStudent(int id)
{
	if (head == NULL)
	{
		// If the list is empty, inform the user
		printf("Student List is Empty.\n");
	}
	else
	{
		node *current = head;
		int found = 0; // Flag to check if student was found

		// Traverse the list to find the student with the given ID
		while (current != NULL)
		{
			if(current -> data.id == id)
			{
				// If found, prompt the user to enter new details
				printf("-----------------------------------------------\n");
				printf("Enter New Details For The Student With ID %d : \n",current -> data.id);
				printf("Enter New Name : ");
				scanf("%s",current -> data.name);
				printf("Enter New Age : ");
				scanf("%d",&current -> data.age);
				printf("Enter New GPA : ");
				scanf("%f",&current -> data.gpa);
				printf("Student Details Updated Successfully.\n");
				found = 1; // Set flag to indicate student was found
				break; // Exit loop as we have updated the student
			}
			else
			{
				current = current -> next; // Move to the next node
			}


		}
		// If the student wasn't found, print a message
		if(!found)
		{
			printf("Student Wasn't Found.\n");
		}

	}
}


// Function to calculate the average GPA of all students
float calculateAverageGPA(void)
{
	if (head == NULL)
	{
		return 0.0; // If the list is empty, return 0.0 as the average GPA
	}
	else

	{
		node *current = head;
		float sum_GPA = 0.0;	// Sum of all GPAs
		int num_students = 0;	// Number of students in the list

		// Traverse the list to calculate the sum of GPAs and count the students
		while (current != NULL)
		{
			sum_GPA += current -> data.gpa;
			num_students +=1;
			current = current -> next;
		}
		// Calculate and return the average GPA
		float Average_GPA = (sum_GPA / num_students); // Calculate average
		return Average_GPA;
	}
}


// Function to find and display the student with the highest GPA
void searchHighestGPA(void)
{
	if (head == NULL)
	{
		// If the list is empty, inform the user
		printf("The Student List is Empty.\n");
	}

	node *current = head;
	node *max_GPA = head; // Initialize max_GPA to the first student

	// Traverse the list to find the student with the highest GPA
	while (current != NULL)
	{
		if (current -> data.gpa > max_GPA -> data.gpa)
		{
			max_GPA = current; // Update max_GPA if a higher GPA is found
		}

		current = current -> next; // else the current moves and searches for the highest GPA
	}

	// Print the details of the student with the highest GPA
	printf ("The Student With The Highest GPA : \n[ ID : %d , Name : %s , Age : %d , GPA : %f ]\n",max_GPA -> data.id , max_GPA -> data.name , max_GPA -> data.age , max_GPA -> data.gpa);
}


// Function to delete a student from the list by ID
void deleteStudent(int id)
{
	if (head == NULL)
	{
		// If the list is empty, inform the user
		printf("The Student List is Empty.\n");
	}
	else
	{
		node *current = head;
		node *prev = NULL;

		// Check if the head node is the one to be deleted
		if (head -> data.id == id)
		{
			head = current -> next; // Move head to the next node
			free(current); // Free memory of the deleted node
			printf("The Student With ID %d is Deleted.\n", id);
			return;
		}

		// Traverse the list to find the node with the matching id
		while (current != NULL && current->data.id != id)
		{
			prev = current;
			current = current -> next;
		}
		// Check if the student was found in the list
		if (current == NULL)
		{
			printf("Student with ID %d wasn't found.\n", id);
		}
		else
		{
			// Link the previous node to the next node, skipping the deleted one
			prev -> next = current -> next;
			printf("The Student With ID %d is Deleted.\n",current -> data.id);
			free(current); // Free memory of the deleted node

		}
	}
}


// Main function to drive the program
int main(void)
{
	// Set buffer modes for stdout and stderr
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// Loop to continuously display the menu and perform actions
	for (;;)
	{
		int choice ;
		student data;
		// Display the menu
		printf("-----------------------------------------------\n");
		printf("1. Add Student\n");
		printf("2. Display Students\n");
		printf("3. Search Student By ID\n");
		printf("4. Update Student Information\n");
		printf("5. Delete Student\n");
		printf("6. Calculate Average GPA\n");
		printf("7. Search For Student With Highest GPA\n");
		printf("8. Exit\n");
		printf("Enter Choice : ");
		scanf("%d",&choice); // Get the user's choice

		// Perform action based on user's choice
		switch (choice)

		{
		case 1 :
			// Get new student details and add to the list
			printf("-----------------------------------------------\n");
			printf("Enter Student's ID : ");
			scanf("%d",&data.id);
			printf("Enter Student's Name : ");
			scanf("%s",data.name);
			printf("Enter Student's Age : ");
			scanf("%d",&data.age);
			printf("Enter Student's GPA : ");
			scanf("%f",&data.gpa);
			printf("-----------------------------------------------\n");
			addStudent(&data);
			break;
		case 2 :
			// Display all students in the list
			printf("-----------------------------------------------\n");
			displayStudents();
			break;
		case 3 :
			// Search for a student by ID
			printf("-----------------------------------------------\n");
			printf("Enter Student ID To Search : ");
			scanf("%d",&data.id);
			searchStudentByID(data.id);
			break;
		case 4 :
			// Update a student's information by ID
			printf("Enter Student ID To Update His/Her Information : ");
			scanf("%d",&data.id);
			updateStudent(data.id);
			break;
		case 5 :
			// Delete a student from the list by ID
			printf("Enter Student ID To Delete His/Her Data : ");
			scanf("%d",&data.id);
			deleteStudent(data.id);
			break;
		case 6 :
			// Calculate and display the average GPA
			printf("Average GPA = %f\n",calculateAverageGPA());
			break;
		case 7 :
			// Find and display the student with the highest GPA
			searchHighestGPA();
			break;
		case 8 :
			// Exit the program
			printf("Exiting the program...\n");
			exit(0); // Exit with status code 0 (success)
			return 0;
		}

	}
}
