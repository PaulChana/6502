# Javascript

## Node versioning
Note, if you use `nvim` to manage node, you will need to ensure that you have a system version of node installed. 
Do this by running

```
brew install node
```

Before running anything you will need to do 

```
npm install
```

## Format on save in VScode

Install the [prettier extension](https://marketplace.visualstudio.com/items?itemName=esbenp.prettier-vscode). 

You will then need to update your VSCode [settings.json](https://vscode.readthedocs.io/en/latest/getstarted/settings/) file, to include the following:
```
"[typescriptreact]": {
    "editor.tabSize": 2,
    "editor.formatOnSave": true,
    "editor.defaultFormatter": "esbenp.prettier-vscode"
},
"[javascript]": {
    "editor.tabSize": 2,
    "editor.formatOnSave": true,
    "editor.defaultFormatter": "esbenp.prettier-vscode"
},
"[typescript]": {
    "editor.tabSize": 2,
    "editor.formatOnSave": true,
    "editor.defaultFormatter": "esbenp.prettier-vscode"
},
"[json]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode"
},
"[html]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode"
},
```