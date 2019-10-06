ThisBuild / scalaVersion := "2.12.10"
ThisBuild / organization := "com.xzr"

lazy val string_calculator = (project in file("."))
  .settings(
    name := "String Calculator",
    libraryDependencies += "org.scalatest" %% "scalatest" % "3.0.5",
  )
