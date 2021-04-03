#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fiche
{
   char nom[11];  
   char prenom[11];
   int age;
};

/* affichage du tableau */
static void aff (struct fiche const *a, size_t n)
{
   size_t i;
   for (i = 0; i < n; i++)
   {
      /* pointeur intermediaire pour alleger l'ecriture */
      struct fiche const *p = a + i;
      printf ("%-10s %-10s %d ans\n", p->nom, p->prenom, p->age);
   }
   
   printf ("\n");
}

/* fonction utilisateur de comparaison fournie a qsort() */
static int compare_prenom (void const *a, void const *b)
{
   /* definir des pointeurs type's et initialise's
      avec les parametres */
   struct fiche const *pa = a;
   struct fiche const *pb = b;

   /* evaluer et retourner l'etat de l'evaluation (tri croissant) */
   return strcmp (pa->prenom, pb->prenom);
}

/* fonction utilisateur de comparaison fournie a qsort() */
static int compare_age (void const *a, void const *b)
{
   struct fiche const *pa = a;
   struct fiche const *pb = b;

   return pa->age - pb->age;
}

/* fonction utilisateur de comparaison fournie a qsort() */
static int compare_age_dec (void const *a, void const *b)
{
   struct fiche const *pa = a;
   struct fiche const *pb = b;

   return pb->age - pa->age;
}

int main (void)
{
/* tableau a trier (tableau de pointeurs sur char const) */
   struct fiche tab[] = {
      {"Simpson", "Homer", 36},
      {"Bouvier", "Marge", 34},
      {"Simpson", "Bart", 10},
      {"Simpson", "Lisa", 8},
      {"Simpson", "Maggie", 2},
   };

/* affichage du tableau dans l'etat */
   aff (tab, sizeof tab / sizeof *tab);

   qsort (tab, sizeof tab / sizeof *tab, sizeof *tab, compare_prenom);

/* affichage du tableau apres le tri */
   aff (tab, sizeof tab / sizeof *tab);

   qsort (tab, sizeof tab / sizeof *tab, sizeof *tab, compare_age);

/* affichage du tableau apres le tri */
   aff (tab, sizeof tab / sizeof *tab);

   qsort (tab, sizeof tab / sizeof *tab, sizeof *tab, compare_age_dec);

/* affichage du tableau apres le tri */
   aff (tab, sizeof tab / sizeof *tab);

   return 0;
}