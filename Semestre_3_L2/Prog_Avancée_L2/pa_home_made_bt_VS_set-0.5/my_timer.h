/*!\file my_timer.h
 * \brief fonctions pour chronométrer le temps passé entre \ref initTimer et \ref getElapsedTime
 * \author Farès BELHADJ, amsi@up8.edu
 * \date October 04 2022
 */
#ifndef MY_TIMER_H
#define MY_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif 

  /*!\brief initialise le timer.
   */
  extern void   initTimer       (void);
  /*!\brief donne le temps passé (en secondes) depuis l'initialisation
   * du timer.
   */
  extern double getElapsedTime  (void);

#ifdef __cplusplus
}
#endif  

#endif /* MY_TIMER */
