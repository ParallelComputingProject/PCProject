# Parallel Computing Project (Coms3009)

--------------------------------------------------------------------------------

## Description:

Project and file structure description here.

## To run(in Unix):

- The bash scripts will produce all required executables and run them.

  #### for the serial version of the code.

  ```sh
    $ cd /Tests/Serial
    $ sudo chmod 777 runSerial.sh
    $ ./runSerial.sh
  ```

  #### for the openMP implementation of the code.

  ```sh
    $ cd /Tests/Parallel
    $ sudo chmod 777 runParallel.sh
    $ ./runParallel.sh
  ```

  #### to clean run (in both Serial or Parallel folders).

  ```sh
    $ make clean
  ```

  _In both the serial and the openMP implementation there is a folder called times and all your tests will be saved in there and you can use **LibreOffice Calc** to create a scatter plot_
