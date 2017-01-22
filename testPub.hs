{-# LANGUAGE OverloadedLists   #-}
{-# LANGUAGE OverloadedStrings #-}

--  Pubsub envelope publisher

-- Next steps: protobufs:
-- https://hackage.haskell.org/package/proto-lens-protoc
-- https://github.com/google/proto-lens
-- https://www.schoolofhaskell.com/user/commercial/content/monad-transformers#lift-vs-liftio

module Main where

import Control.Concurrent
import Control.Monad
import System.ZMQ4.Monadic

main :: IO ()
main = runZMQ $ do
    -- Prepare our publisher
    publisher <- socket Pub
    connect publisher "tcp://127.0.0.1:5555"

    forever $ do
        send publisher [] "ABC"
        liftIO $ threadDelay 1000000

