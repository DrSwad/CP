# Notebook Generator



### Required Packages

* python3

  ```bash
  sudo apt-get install python3
  ```

* pygments

  ```bash
  sudo apt-get install python3-pip
  pip3 install pygments
  ```

* texlive-full

  ```bash
  sudo apt-get install texlive-full
  ```



### How To Use

Put your codes in the **code** folder. You can create subfolders (E.g. - Graph, String, Math etc.) for different categories.

Open a terminal and run - 

```bash
  python3 main.py
```



### Customization

To customize you need to edit the ```template/template.tex``` file.

- To change font size, edit line 1 or change ``scaled=..`` in line 11 (more flexible).
- To change university name, edit line 65.
- To change team name, edit line 67.
- To change team member names, edit line 68.
- To change # of columns in toc, edit line 85.
- To change # of columns in codes, edit line 89.
