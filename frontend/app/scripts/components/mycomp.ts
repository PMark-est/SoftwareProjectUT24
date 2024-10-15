/** @format */
import angular from "angular"
import { html } from "@/util"

export default angular.module("korpApp").component("mycomp", {
    template: html`<span class="pl-4">
        Filter:
        <uib-dropdown>
            <button uib-dropdown-toggle type="button">Dropdown <span class="caret"></span></button>
            <ul uib-dropdown-menu>
                <li ng-repeat="">
                    <a href="" ng-click=""></a>
                </li>
            </ul>
        </uib-dropdown>
    </span>`,
    bindings: {
        kwicHits: "<",
    },
    controller: function () {
        let $ctrl: any = this

        $ctrl.$onChanges = (changes) => {
            if ($ctrl.kwicHits !== undefined) {
                console.log("Updated kwicHits:", $ctrl.kwicHits)
            }
        }
    },
})
