function startScript()
  --Loads the level loader script
  print("Loading: " .. path  .. level .. "\\" .. loaderScript)
  dofile(path .. level .. "\\" .. loaderScript);
  startScript();
  
  --Loads itself just for test in case of calling the function again (Isn't required. Because after loading we should close the script)
  --dofile(path .. loaderScript)
end

--This is the path of the scripts folder (It should be changed by the application)
path = "C:\\" --"E:\\UNICENP\\TCC\\Source\\jogoshadow\\TCC\\Scripts\\"

--This is the level that we are going to load (It should be changed by the application)
level = "Level1"

--This should be a constant but whatever.
loaderScript = "loader.lua"