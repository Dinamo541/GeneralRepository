document.addEventListener('DOMContentLoaded', () => {
    const nameInput = document.querySelector('.name');
    const passwordInput = document.querySelector('.password');
    const button = document.querySelector('button');
    const title = document.querySelector('.title');

    function updateButtonState() {
        if (nameInput.value.trim() && passwordInput.value.trim()) {
            button.classList.add('active');
            button.classList.remove('disactive');
        } else {
            button.classList.add('disactive');
            button.classList.remove('active');
        }
    }

    function updateTitleState() {
        if (nameInput.value.trim() && passwordInput.value.trim()) {
            title.classList.add('active');
            title.classList.remove('disactive');
        } else {
            title.classList.add('disactive');
            title.classList.remove('active');
        }
    }

    nameInput.addEventListener('input', updateButtonState);
    passwordInput.addEventListener('input', updateButtonState);
    nameInput.addEventListener('input', updateTitleState);
    passwordInput.addEventListener('input', updateTitleState);

    updateButtonState();
    updateTitleState();
});
