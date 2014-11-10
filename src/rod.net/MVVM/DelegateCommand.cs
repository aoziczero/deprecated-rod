using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Rod.Net.MVVM
{
    public class DelegateCommand : ICommand
    {
        private readonly Func<bool> _can_execute;
        private readonly Action _execute;

        public event EventHandler CanExecuteChanged;

        public DelegateCommand(Action execute)
            : this(execute, null)
        {
        }

        public DelegateCommand(Action execute,
                       Func<bool> canExecute)
        {
            _execute = execute;
            _can_execute = canExecute;
        }

        public bool CanExecute(object parameter)
        {
            if (_can_execute == null)
            {
                return true;
            }

            return _can_execute();
        }

        public void Execute(object parameter)
        {
            _execute();
        }

        public void RaiseCanExecuteChanged()
        {
            if (CanExecuteChanged != null)
            {
                CanExecuteChanged(this, EventArgs.Empty);
            }
        }
    }
}
