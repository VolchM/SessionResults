using System;
using System.Collections.Generic;
using System.Text;

namespace SessionResultsCS.UI
{
    public abstract class LoopPage: IPage
    {
        private bool _looping;

        private MenuActionPicker? _picker;

        public void Start()
        {
            _looping = true;
            while (_looping)
            {
                Loop();
                Console.WriteLine("Действия: ");
                _picker?.PickAndRun();
            }
        }

        protected abstract void Loop();

        protected void SetPicker(MenuActionPicker picker)
        {
            _picker = picker;
        }

        protected void StopLoop()
        {
            _looping = false;
        }
    }
}
