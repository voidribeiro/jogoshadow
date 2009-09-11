function startScript()
  --configure the scripts path
  levelScriptsPath = path .. "Scripts\\" .. level .. "\\"
  --Loads the level loader script
  
  --Just testing
  local factory = Factory.GetInstance()
  print(factory:Create(3,"E:\\UNICENP\\TCC\\Source\\jogoshadow\\TCC\\resources\\faerie.md2"))
  
  print("Loading: " .. levelScriptsPath .. loaderScript)
  dofile(levelScriptsPath .. loaderScript);
  startScript();
  
  --Loads itself just for test in case of calling the function again (Isn't required. Because after loading we should close the script)
  --dofile(path .. loaderScript)
end

--This is the path of the executable folder (It should be changed by the application)
path = "" --"E:\\UNICENP\\TCC\\Source\\jogoshadow\\TCC\\"
--This is the level that we are going to load (It should be changed by the application)
level = "" --"Level1"

--This will show the path of the current level to be loaded
levelScriptsPath = ""
--This should be a constant but whatever.
loaderScript = "loader.lua"