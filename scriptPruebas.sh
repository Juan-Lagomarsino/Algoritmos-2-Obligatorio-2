#!/bin/bash

echo "Ingrese numero de ejercicio: "
read i

# Compila el ejercicio
g++ -std=c++11 -O2 -o ejercicio$i ejercicio$i.cpp

# Directorio base de tests
DIR="tests/ejercicio$i"

if [ ! -d "$DIR" ]; then
  echo "No existe el directorio $DIR"
  exit 1
fi

echo "==============================="
echo "Ejecutando pruebas para ejercicio $i"
echo "==============================="

# Recorre todos los archivos de entrada que terminen en .in.txt
for in_file in "$DIR"/*.in.txt; do
  # Si no hay ninguno, corta
  [ -e "$in_file" ] || { echo "No se encontraron archivos .in.txt en $DIR"; exit 1; }

  base_name=$(basename "$in_file" .in.txt)
  out_file="$DIR/$base_name.out.txt"
  prueba_file="$DIR/$base_name.prueba.ahora.txt"

  echo "➡️  Prueba: $base_name"

  # Ejecuta el programa
  ./ejercicio$i < "$in_file" > "$prueba_file"

  # Compara salidas ignorando espacios y saltos de línea extra
  if diff -qw "$out_file" "$prueba_file" > /dev/null; then
    echo "✅ OK"
  else
    echo "❌ Diferencias encontradas (ignorando espacios):"
    diff -w "$out_file" "$prueba_file" | head -n 10
  fi
  echo "--------"
done

echo "Pruebas finalizadas."
