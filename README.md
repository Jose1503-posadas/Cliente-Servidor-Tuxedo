# Cliente-Servidor-Tuxedo

Compilacion
1. Ubicarse en la ruta del archivo makefile
     - cd /home/oracle/tuxedo/make
2. Compilar el archivo makefile con su respectivo nombre
    - make -f makefileT3
3. Ubicarse en la ruta del archivo ubbconfig (tuxconfigT3)
    - cd ../conf
4. Ejecutar los siguientes comandos
   - tmloadcf -y tuxconfigT3
   - tmboot -y
   - tmadmin
     - psc
5. Ubicarse en la ruta de los binarios /bin
     - cd ../bin
7. Ejecutar el archivo sin parametro para ver las instrucciones
     - ./clienteT3
7. A partir de las instrucciones compilar
     - ./cliente 1 2 4 0 0 0 0
8. Ir al la ruta de los archivos log /log
     - cd ../log
9. Ejecutar el archivo ULOG con su respectivo nombre (Se ven los servicios que se ejecutaron)
     - tail -13 ULOG-S10.010524


En caso de que se encuentre activo el servicio de tuxedo dar de baja con el comando
     - tmshutdown -y
