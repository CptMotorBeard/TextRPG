import os
from shutil import copyfile

allStates = [
"StateBuildingUpgrades",
"StateCharacterCreation",
"StateCharacterOverview",
"StateCityUpgrades",
"StateCombat",
"StateDiplomacy",
"StateFactionCreation",
"StateFactionOverview",
"StateInventory",
"StateLoadGame",
"StateMainMenu",
"StateSaveGame",
"StateUnitUpgrades",
"StateWorldOverview"
]

baseFile = "__BASESTATE.lua"
commentEnd = ']]--'

openFile = open(baseFile, 'r')
readFile = openFile.read()
endOfComment = readFile.find(commentEnd)
commentInfo = readFile[0:endOfComment] + commentEnd
openFile.close()

directoryFiles = [file for _, _, file in os.walk('.')][0]

for state in allStates:
    stateFile = state + '.lua'
    if (stateFile not in directoryFiles):
        ## Create a new LUA file
        print(f'Creating new file [{stateFile}]')
        copyfile(baseFile, stateFile)
    else:
        ## Update the comment
        print(f'Updating file [{stateFile}]')
        copyfile(stateFile, state + '.bak')
        f = open(stateFile, 'r')
        r = f.read()
        c = r.find(commentEnd)
        fileStart = c + len(commentEnd)
        newSource = commentInfo + r[fileStart:]
        f.close()
        f = open(stateFile, 'w')
        f.write(newSource)
        f.close()
