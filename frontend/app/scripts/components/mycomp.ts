/** @format */
import angular from "angular"
import { html } from "@/util"

export default angular.module("korpApp").component("mycomp", {
    template: html`<span class="pl-4">
        Filter:
        <uib-dropdown>
            <button uib-dropdown-toggle type="button">Dropdown <span class="caret"></span></button>
            <ul uib-dropdown-menu>
                <li ng-repeat="item in $ctrl.menuItems">
                    <a href="" ng-click="$ctrl.selectItem(item)">{{ item.name }}</a>
                </li>
            </ul>
        </uib-dropdown>
    </span>`,
    bindings: {},
    controller: () => {},
})
