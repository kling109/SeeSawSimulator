/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 380 Operating Systems
Last Date Modified: 8 April 2019
Project: See-Saw Simulator
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

using namespace std;

double velocity = 0;
double height = 1.0;
int t = 0;
sem_t fredGo, wilmaGo;
pthread_t threads[2];

/*
A method to managae the "fred" side of the see-saw.  Fred handles updating position,
adjusting velocity when he reaches the ground, and calculating number of cycles completed.
A semaphore is used to synchronize the program, ensuring that the velocity is updated before
Fred adjusts the height.
*/
void* fredSee(void* ph)
{
  while (t < 11)
  {
    sem_wait(&fredGo);
    if (height <= 1.0)
    {
      velocity = 1.0;
      ++t;
    }
    sem_post(&fredGo);
    sem_wait(&wilmaGo);
    sem_post(&wilmaGo);
    sleep(1);
    cout << "Fred Curent Height: " << height << endl;
    cout << "Wilma Current Height: " << 8.0 - height << endl;
    height += velocity;
  }
}


/*
Since Fred does all the calculations and recording, Wilma only must check if her height is low enoough
to need to adjust velocity.
*/
void* wilmaSaw(void* ph)
{
  while (t < 11)
  {
    sem_wait(&wilmaGo);
    sem_wait(&fredGo);
    if (height >= 7.0)
    {
      velocity = -1.5;
    }
    sem_post(&wilmaGo);
    sem_post(&fredGo);
  }
}

/*
The main method initializes the threads, sets their functions, and runs the program
only if the threads are properly established.
*/
int main(int argc, char** argv)
{
  if (sem_init(&fredGo, 0, 1) != 0 || sem_init(&wilmaGo, 0, 1) != 0)
  {
    cout << "Initializing the semaphore failed.  The program will now exit." << endl;
    return 1;
  }
  bool setup1 = pthread_create(&threads[0], NULL, &fredSee, NULL);
  bool setup2 = pthread_create(&threads[1], NULL, &wilmaSaw, NULL);
  if (setup1 || setup2)
  {
    cout << "Initializing threads failed.  The program will now exit." << endl;
    return 1;
  }
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  cout << "Simulation Complete." << endl;
  return 0;
}
