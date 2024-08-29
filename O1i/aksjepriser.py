
import time
import random

#Algoritme for å finne beste dagene å kjøpe og selge på
def finn_beste_dager(kursForandring):
    maks_profitt = 0 # største nåværende profitt
    kjop_dag = 0 # dag å kjøpe på
    selg_dag = 0 # dag å selge på
    n = len(kursForandring)

    for i in range(n): # i er dagen å kjøpe
        pris_naa = 0
        for j in range(i+1, n): # j er dagen å selge
            pris_naa += kursForandring[j]
            profitt = pris_naa - kursForandring[i]
            if profitt > maks_profitt:
                maks_profitt = profitt
                kjop_dag = i
                selg_dag = j

    return kjop_dag+1 , selg_dag+1


#Test data
def generer_test_data(lengde):
    return [random.randint(-10, 10) for _ in range(lengde)]


#Tar tiden på algoritmen med et gitt datasett
def tid_taking(test_data):
    start_tid = time.time()
    finn_beste_dager(test_data)
    slutt_tid = time.time()
    return slutt_tid - start_tid

test_data_1000 = generer_test_data(1000)
test_data_5000 = generer_test_data(5000)
test_data_10000 = generer_test_data(10000)

tid_1000 = tid_taking(test_data_1000)
tid_5000 = tid_taking(test_data_5000)
tid_10000 = tid_taking(test_data_10000)

print(f"Tid for array med lengde 1000: {tid_1000:.6f} sekunder")
print(f"Tid for array med lengde 5000: {tid_5000:.6f} sekunder")
print(f"Tid for array med lengde 10000: {tid_10000:.6f} sekunder")


