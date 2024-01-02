const buttonAdd = document.querySelector('#add')
let directive_index = 1
let directive_index_tab = [0]

function createDirective(){
    const box = document.createElement('div')
    box.classList.add(`box`)
    box.innerHTML = 
        `<input type="text" name="directory${directive_index}" class="directory" placeholder="Directory" required>
        <input type="text" name="scriptalias${directive_index}" class="directory" placeholder="ScriptAlias">
        <div class="directive">
            <div>
                <label>AllowOverride : </label><select name="allowoverride${directive_index}">
                    <option value="all">All</option>
                    <option value="none">None</option>
                </select>
            </div>
            <div>
                <input type="checkbox" name="indexes${directive_index}">
                <label>Indexes</label>
            </div>
            <div>
                <input type="checkbox" name="followsymlinks${directive_index}">
                <label>FolowSymLinks</label>
            </div>
            <div>
                <input type="checkbox" name="execcgi${directive_index}">
                <label>ExecCGI</label>
            </div>
        </div>
        <button item="${directive_index}" class="del${directive_index}">Delete</button>`
        
    buttonAdd.insertAdjacentElement("beforebegin",box)

    document.querySelector(`.del${directive_index}`).addEventListener('click',function(event){
        event.preventDefault()
        deleteDirective(event.currentTarget)
    })
    
    directive_index_tab.push(directive_index)
    directive_index++
}

function deleteDirective(button){
    const i = parseInt(button.getAttribute('item'))
    let tmp = []
    for(e of directive_index_tab){
        if(e !== i){
            tmp.push(e)
        }
    }
    directive_index_tab = tmp
    button.parentElement.remove()
    printDirectoryIndexTab()
}

buttonAdd.addEventListener('click',function(event){
    event.preventDefault()
    createDirective()
    printDirectoryIndexTab()
})

function printDirectoryIndexTab(){
    const str = directive_index_tab.join(' ')
    document.querySelector('.tab').setAttribute('value',str)
    document.querySelector('.tab_len').setAttribute('value',directive_index_tab.length)
}

