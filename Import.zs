hvar hMap
set hMap <GetMap "HF">
if <not <project.IsInit>>
  project.InitProject
endif

// initialise and edit file selector
filesel FS
filesel.Init &FS true NULL "Heightfield files|*.bmp;|All files (*.*)|*.*|" NULL NULL
assert <EditUI &FS "Select heightfield to import"> "Import aborted"


// initialise and edit settings list
//assert <EditUI &ls "Import Height Map"> "Import aborted"

// Load the map
map finalMap
assert <map.LoadFile2 hMap <filesel.GetPathA &FS> HF false true> "Error loading file"

// To set the scale of the heightmap
assert <map.SetHorizScale hMap 5> "Failed operation!"



map.SetFlag hMap 1 true // set 'Ready' flag
map.SetFlag hMap 5 false // clear 'modified' flag

// refresh the heightfield
view.ShowMap "HF"
