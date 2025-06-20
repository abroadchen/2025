import { SyncHook, SyncBailHook, SyncWaterfallHook, SyncLoopHook, AsyncParallelHook, AsyncParallelBailHook, AsyncSeriesHook, AsyncSeriesBailHook, AsyncSeriesWaterfallHook } from "tapable"

const sh = new SyncHook(["msg"])

sh.tap("1", (msg) => { console.log(1, msg) })
sh.call("hello")