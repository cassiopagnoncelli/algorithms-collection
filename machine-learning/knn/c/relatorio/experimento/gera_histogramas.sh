#!/bin/bash

# para chebyschev
./otim_chebyschev training testing --normalizar=0 hist_chebyschev_0 > tx_chebyschev_0
./otim_chebyschev training testing --normalizar=1 hist_chebyschev_1 > tx_chebyschev_1

# para euclidiana
./otim_euclidiana training testing --normalizar=0 hist_euclidiana_0 > tx_euclidiana_0
./otim_euclidiana training testing --normalizar=1 hist_euclidiana_1 > tx_euclidiana_1

# para manhattan
./otim_manhattan training testing --normalizar=0 hist_manhattan_0 > tx_manhattan_0
./otim_manhattan training testing --normalizar=1 hist_manhattan_1 > tx_manhattan_1

# para minkowski
./otim_minkowski_3 training testing --normalizar=0 hist_minkowski_3_0 > tx_minkowski_3_0
./otim_minkowski_3 training testing --normalizar=1 hist_minkowski_3_1 > tx_minkowski_3_1
./otim_minkowski_4 training testing --normalizar=0 hist_minkowski_4_0 > tx_minkowski_4_0
./otim_minkowski_4 training testing --normalizar=1 hist_minkowski_4_1 > tx_minkowski_4_1
./otim_minkowski_5 training testing --normalizar=0 hist_minkowski_5_0 > tx_minkowski_5_0
./otim_minkowski_5 training testing --normalizar=1 hist_minkowski_5_1 > tx_minkowski_5_1
./otim_minkowski_6 training testing --normalizar=0 hist_minkowski_6_0 > tx_minkowski_6_0
./otim_minkowski_6 training testing --normalizar=1 hist_minkowski_6_1 > tx_minkowski_6_1

