using System;
using System.Collections.Generic;
using System.Text;

namespace SessionResultsCS.UI
{
    public abstract class LoopPage: IPage
    {
        private bool _looping;

        public void Start()
        {
            _looping = true;
            while (_looping)
            {
                Loop();
            }
        }

        protected abstract void Loop();

        protected void StopLoop()
        {
            _looping = false;
        }
    }
}
