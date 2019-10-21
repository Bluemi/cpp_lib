--[[
--	this bam script creates targets corresponding to the directories src/*
--	those are named like the corresponding folder
--
--	e.g. src/template_specialization
--	target to compile: "template_specialization"
--	target to run:     "r_template_specialization"
--
--	target to compile all: "c"
--	target to run     all: "r"
--
--	"compile" is the default target
--]]

conf = ScriptArgs["conf"] or "debug"
build_dir = ScriptArgs["build_dir"] or "build"
build_dir = PathJoin(build_dir, conf)
src_dir = "src"

AddTool(function(s)
	if conf == "debug" then
		s.debug = 1
		s.optimize = 0
	elseif conf == "release" then
		s.debug = 0
		s.optimize = 1
	end

	s.cc.flags:Add("-Wall")
	s.cc.flags_cxx:Add("--std=c++2a")
	s.cc.includes:Add("src")
	s.cc.Output = function(s, input)
		input = input:gsub("^src/", "")
		return PathJoin(PathJoin(build_dir, "obj"), PathBase(input))
	end
	s.link.Output = function(s, input)
		return PathJoin(build_dir, PathBase(input))
	end
end)

s = NewSettings()
targets = CollectDirs(PathJoin(src_dir, "*"))

PseudoTarget("c")
DefaultTarget("c")
PseudoTarget("r", "c")

for _, target in ipairs(targets) do
	local name = target:gsub("^src/", "")
	local run = "r_"..name

	local src = CollectRecursive(PathJoin(target, "*.cpp"))
	local obj = Compile(s, src)
	local bin = Link(s, name, obj)

	PseudoTarget(name, bin)
	PseudoTarget(run, name)
	AddJob(run, "running "..name.."...", PathJoin(build_dir, name))
	AddDependency("c", name)
	AddDependency("r", run)
end
